#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <exception>

#include "logger.hpp"

class Arguments {

public:
    void analyseArguments(int argc, char **argv);
    int getThreadsNumber();
    std::string getHashedPassword();
private:
    int threadsNumber = 4;
    std::string hashedPassword = "";
};

#endif