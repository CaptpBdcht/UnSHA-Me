#include <iostream>
#include <sstream>
#include "../include/logger.hpp"

int main(int argc, char **argv) {
    Logger log;

    log.info(std::stringstream() << "test");

    return EXIT_SUCCESS;
}