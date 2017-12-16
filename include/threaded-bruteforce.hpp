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
#include <iomanip>
#include <atomic>

#include "logger.hpp"
#include "bruteforce.hpp"

#define MIN_WORD_SIZE 1
#define MAX_WORD_SIZE 20

class ThreadedBruteforce {

public:
    ThreadedBruteforce(uint8_t, std::string, Bruteforce*);
    virtual ~ThreadedBruteforce() = default;

    void threadedBruteforcer(uint8_t);

//    std::deque<std::thread> &getBruteforcers();

    const uint8_t getNbThreads() const;

private:
    const uint8_t nbThreads;
//    std::deque<std::thread> bruteforcers;
    std::mutex mutex;
    std::condition_variable cv;
    const std::string hashedPass;

    std::atomic<bool> foundHash;
    Bruteforce* bruteforce;
};

#endif