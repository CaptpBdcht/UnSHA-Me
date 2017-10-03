#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include <omp.h>
#include <openssl/sha.h>
#include <omp.h>
#include <iomanip>

#include "logger.hpp"

class Bruteforce {
    
public:
    Bruteforce(int, std::string);
    void startBruteforce();
    std::string checkGeneratedWordsByLength(const char *, uint8_t);
    bool isSearchedSHA256Hash(const std::string &);

private:
    const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    int nbThreads;
    std::string hashedPassword;
    uint8_t minPassLength = 1;
    uint8_t maxPassLength = 100;
};

#endif