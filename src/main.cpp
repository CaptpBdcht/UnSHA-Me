#include "../include/arguments.hpp"
#include "../include/bruteforce.hpp"

int main(int argc, char **argv) {

    Arguments arguments;

    arguments.analyseArguments(argc, argv);

    Bruteforce bruteforce(arguments.getThreadsNumber(), arguments.getHashedPassword());

    bruteforce.startBruteforce();

    return EXIT_SUCCESS;
}