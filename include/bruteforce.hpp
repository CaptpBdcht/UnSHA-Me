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
    Bruteforce(std::string);
    void startBruteforce(uint8_t);
    std::string checkGeneratedWordsByLength(const char *, uint8_t);
    bool isSearchedSHA256Hash(const std::string &);

private:
    const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    std::string hashedPassword;
};

#endif