#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

#include "../include/arguments.hpp"
#include "../include/bruteforce.hpp"
#include "../include/logger.hpp"
#include "../include/threaded-bruteforce.hpp"

int main(int argc, char **argv) {
    
    Logger log;
    
    Arguments arguments;

    arguments.analyseArguments(argc, argv);

    ThreadedBruteforce tbf(
        arguments.getThreadsNumber(),
        arguments.getHashedPassword()
    );

    return EXIT_SUCCESS;
}