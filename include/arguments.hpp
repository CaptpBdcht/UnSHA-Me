#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <exception>

#include "logger.hpp"

class Arguments {

public:
    void analyseArguments(int, char **);
    uint8_t getThreadsNumber();
    std::string getHashedPassword();

private:
    uint8_t threadsNumber = 4;
    std::string hashedPassword = "";
};

#endif