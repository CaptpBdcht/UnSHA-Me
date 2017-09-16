#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>

class ThreadPool {
    
    public:
        ThreadPool(const uint8_t threadsNumber);
    
    private:
        uint8_t poolSize;
};

#endif