#include "../include/arguments.hpp"
#include "../include/threaded-bruteforce.hpp"
#include "../include/HashProducer.h"

using namespace std;

void generateHashes(HashProducer *producer);

int main(int argc, char **argv) {

    Arguments arguments;

    arguments.analyseArguments(argc, argv);

//    ThreadedBruteforce tbf(
//            arguments.getThreadsNumber(),
//            arguments.getHashedPassword()
//    );

    HashProducer *hashProducer = new HashProducer();
    thread producer(generateHashes, hashProducer);

    producer.join();

    delete hashProducer;

    return EXIT_SUCCESS;
}

void generateHashes(HashProducer *producer) {
    producer->startWordGeneration();
}