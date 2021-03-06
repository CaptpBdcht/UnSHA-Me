#ifndef THREADED_BRUTEFORCE_H
#define THREADED_BRUTEFORCE_H

#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <algorithm>
#include <vector>
#include <omp.h>
#include <iomanip>
#include <atomic>

#include "sha.h"
#include "logger.hpp"

#define MIN_WORD_SIZE 1
#define MAX_WORD_SIZE 20

class ThreadedBruteforce {

public:
    ThreadedBruteforce(uint8_t, std::string);
    ~ThreadedBruteforce();
    void threadedBruteforcer(uint8_t);
    std::string startBruteforceByWordLength(uint8_t);
    bool isSearchedSHA256Hash(char **, SHA256_CTX);

private:
    const uint8_t nbThreads;
    std::deque<std::thread> bruteforcers;
	std::mutex mutex;
	std::condition_variable cv;
    const std::string hashedPass;
    const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    
    std::atomic<bool> foundHash;
};

#endif