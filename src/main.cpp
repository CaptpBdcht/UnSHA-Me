#include "../include/arguments.hpp"
#include "../include/threaded-bruteforce.hpp"
#include "../include/HashProducer.h"
#include "../include/Consumer.h"

using namespace std;

void generateHashes(HashProducer *);

void startConsuming(Consumer);

void startBruteForce(ThreadedBruteforce *, uint8_t);

int main(int argc, char **argv) {

    Arguments arguments;

    arguments.analyseArguments(argc, argv);

    Bruteforce *bruteforce = new Bruteforce(arguments.getHashedPassword());

    std::vector<std::thread> threads;
//    std::vector<Bruteforce*> bruteforces;
//
//    for (uint8_t i = 1; i <= arguments.getThreadsNumber(); ++i) {
//        bruteforces.emplace_back(new Bruteforce(arguments.getHashedPassword()));
//    }

    ThreadedBruteforce *tbf = new ThreadedBruteforce(
            arguments.getThreadsNumber(),
            arguments.getHashedPassword(),
            bruteforce
    );

    for (uint8_t i = 1; i <= tbf->getNbThreads(); ++i) {
        threads.emplace_back(std::thread(std::bind(startBruteForce, tbf, i)));
    }

    for (auto &thread: threads) {
        thread.join();
    }

    delete bruteforce;
    delete tbf;

//    HashProducer *hashProducer = new HashProducer();
//    thread producer(generateHashes, hashProducer);
//
//    vector<thread> consumers;
//
//    for (int i = 0; i < arguments.getThreadsNumber(); ++i) {
//        consumers.emplace_back(thread(startConsuming,
//                                      Consumer(arguments.getHashedPassword(), hashProducer)));
//    }
//
//    for (auto &consumer : consumers) {
//        consumer.join();
//    }
//    producer.join();
//
//    delete hashProducer;

    return EXIT_SUCCESS;
}

void startBruteForce(ThreadedBruteforce *threadedBruteforce, uint8_t i) {
    threadedBruteforce->threadedBruteforcer(i);
//    for (uint8_t i = 1; i <= threadedBruteforce->getNbThreads(); ++i) {
//        threadedBruteforce->threadedBruteforcer(i);
//        bruteforcers.emplace_front(std::thread(
//                &ThreadedBruteforce::threadedBruteforcer,
//                this, i
//        ));
//    }
}

void generateHashes(HashProducer *producer) {
    producer->startWordGeneration();
}

void startConsuming(Consumer consumer) {
    cout << "lanching thread..." << endl;
    consumer.startConsuming();
}