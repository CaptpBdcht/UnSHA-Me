#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>

#include <iomanip>
#include <thread>
#include <deque>
#include <map>

#include "sha.h"
#include "logger.hpp"

class Bruteforce {

public:
    explicit Bruteforce(std::string);

    virtual ~Bruteforce();

    bool startBruteforceByWordLength(uint8_t);

    bool isSearchedSHA256Hash(char **, SHA256_CTX&);

    void notifyHashFound();

private:
    const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    bool shouldStop;
    std::string hashedPassword;
    std::mutex hashMutex;
};

#endif