#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "player/Buffer.h"
#include "player/input_plugins/WavInput.h"
#include "player/output_plugins/PulseaudioOutput.h"

bool ended = false;

void producer(player::WavInput& input, player::Buffer& buffer) {
    while (true) {
        player::Buffer::Position wPos = buffer.getWritePosition();
        size_t n = input.read(wPos);
        buffer.markWritten(n);

        if (n == 0) {
            if (input.reachedEOF()) {
                ended = true;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds {1});
            continue;
        }
    }
}

void consumer(player::PulseaudioOutput& output, player::Buffer& buffer) {
    while (true) {
        player::Buffer::Position rPos = buffer.getReadPosition();
        size_t n = output.write(rPos);
        buffer.markRead(n);

        if (n == 0) {
            if (ended) 
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds {1});
            continue;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <wav_file>\n";
        return 1;
    }
    
    /* Create Buffer, Input and Output objects */
    player::Buffer buffer {144, 24576, 1024};

    std::string filename {argv[1]};
    player::WavInput input{filename, buffer};

    player::PulseaudioOutput output {buffer};
    output.open(input.getSampleFormat());

    /* Create consumer and producer threads */
    std::thread producerThread {producer, std::ref(input), std::ref(buffer)};
    std::thread consumerThread {consumer, std::ref(output), std::ref(buffer)};

    /* Free all resources and terminate */
    producerThread.join();
    consumerThread.join();
    std::cout << "here\n";

    output.close();
    return 0;
}
