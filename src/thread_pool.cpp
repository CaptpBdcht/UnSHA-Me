#include "../include/thread_pool.hpp"

ThreadPool::ThreadPool(const uint8_t threadsNumber = 2) : 
    poolSize(threadsNumber) {}
