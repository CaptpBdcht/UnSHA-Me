#include "../include/arguments.hpp"

void Arguments::analyseArguments(int argc, char **argv) {

    Logger log;

    try {
        if (argc < 3)
            throw std::string("Wrong number of arguments.");
        
        threadsNumber = std::stoi(argv[1]);
        hashedPassword = argv[2];
    }
    catch (std::string const& str) {
        log.error(std::stringstream() << str);
        exit(EXIT_FAILURE);
    }
    catch (std::exception const& e) {
        log.error(std::stringstream() << e.what());
        exit(EXIT_FAILURE);
    }
}

int Arguments::getThreadsNumber() {
    return threadsNumber;
}

std::string Arguments::getHashedPassword() {
    return hashedPassword;
}