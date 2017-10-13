#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include <openssl/sha.h>
#include <iomanip>

#include "logger.hpp"

class Bruteforce {
    
public:
    Bruteforce(std::string);
    std::string startBruteforceByWordLength(uint8_t);
    bool isSearchedSHA256Hash(const std::string &, SHA256_CTX);

private:
    const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    std::string hashedPassword;
};

#endif