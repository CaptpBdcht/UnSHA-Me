#include "../include/arguments.hpp"
#include "../include/threaded-bruteforce.hpp"

using namespace std;

void startBruteForce(ThreadedBruteforce *, uint8_t);

int main(int argc, char **argv) {

    Arguments arguments;

    arguments.analyseArguments(argc, argv);

    Bruteforce *bruteforce = new Bruteforce(arguments.getHashedPassword());

    std::vector<std::thread> threads;

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

    return EXIT_SUCCESS;
}

void startBruteForce(ThreadedBruteforce *threadedBruteforce, uint8_t i) {
    threadedBruteforce->threadedBruteforcer(i);
}