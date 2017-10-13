#include "../include/arguments.hpp"
#include "../include/threaded-bruteforce.hpp"

int main(int argc, char **argv) {

    Arguments arguments;

    arguments.analyseArguments(argc, argv);

    ThreadedBruteforce tbf(
        arguments.getThreadsNumber(),
        arguments.getHashedPassword()
    );

    return EXIT_SUCCESS;
}