#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>

#include "player/Buffer.h"
#include "player/Producer.h"
#include "player/Consumer.h"



int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <audio file>\n";
        return 1;
    }

    
    // Create Buffer, Input and Output objects
    player::Buffer buffer {144, 24576, 1024};

    std::string filename {argv[1]};

    player::Producer producer{buffer};
    producer.setTrack(filename);

    player::Consumer consumer{buffer};
    consumer.openOutput(producer.getCurrentSampleFormat());

    // Create consumer and producer threads
    std::thread producerThread {&player::Producer::run, &producer};
    std::thread consumerThread {&player::Consumer::run, &consumer};

    // Commands
    char c;
    while (std::cin >> c) {
        if (c == 'p') {
            producer.produce();
            consumer.consume();
        }
        if (c == 's') {
            producer.pause();
            consumer.pause();
        }
        if (c == 'q') {
            producer.exit();
            consumer.exit();
            break;
        }
    }


    // Free all resources and terminate
    producerThread.join();
    consumerThread.join();

    return 0;
}
