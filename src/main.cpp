#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>

#include "player/Buffer.h"
#include "player/Input.h"
#include "player/InputFactory.h"
#include "player/Output.h"
#include "player/OutputFactory.h"


bool ended = false;

void producer(player::Input *input, player::Buffer& buffer) {
    while (true) {
        player::Buffer::Position wPos = buffer.getWritePosition();
        size_t n = input->read(wPos);
        buffer.markWritten(n);

        if (n == 0) {
            if (input->reachedEOF()) {
                ended = true;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds {1});
            continue;
        }
    }
}

void consumer(player::Output* output, player::Buffer& buffer) {
    while (true) {
        player::Buffer::Position rPos = buffer.getReadPosition();
        size_t n = output->write(rPos);
        buffer.markRead(n);

        if (n == 0) {  // TODO: bad, output buffer may still be playing dat
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
    std::unique_ptr<player::Input> input = player::InputFactory::create(filename);

    std::unique_ptr<player::Output> output = player::OutputFactory::create();
    output->open(input->getSampleFormat());

    /* Create consumer and producer threads */
    std::thread producerThread {producer, input.get(),  std::ref(buffer)};
    std::thread consumerThread {consumer, output.get(), std::ref(buffer)};

    /* Free all resources and terminate */
    producerThread.join();
    consumerThread.join();

    output->close();
    return 0;
}
