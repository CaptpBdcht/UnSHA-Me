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
#include <openssl/sha.h>
#include <omp.h>
#include <iomanip>

#include "logger.hpp"

#define MIN_SIZE 1
#define MAX_SIZE 20

class ThreadedBruteforce {

public:
    ThreadedBruteforce(uint8_t, std::string);
    ~ThreadedBruteforce();
    void threadedBruteforcer(uint8_t);

private:
    const uint8_t nbThreads;
    std::deque<std::thread> bruteforcers;
	std::mutex mutex;
	std::condition_variable cv;
    const std::string hashedPass;
    
    bool foundHash = false;
};

#endif