#ifndef UNSHA_ME_HASHPRODUCER_H
#define UNSHA_ME_HASHPRODUCER_H

#include <condition_variable>
#include <cstring>
#include <map>
#include <mutex>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <deque>

#include "sha.h"
#include "HashConsumer.h"

/** Simple class that generates a hash. */
class HashProducer {
public:
    explicit HashProducer(std::string alphabet = "abcdefgh");//"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");

    /** Generates all anagram of the current alphabet. */
    void startWordGeneration();

    bool isHashAvailable();

    bool isRunning();

    const std::string consumeWord();

    void notifyHashFound(bool hashFound, std::string);
private:
    std::string alphabet;
    bool shouldStop;
    std::map<std::string, std::string> generatedHashesMap; // Pair value of <Hash, Original Word>
    std::deque<std::string> generatedHashes; // Pair value of <Hash, Original Word>
    std::mutex mutex;
    std::mutex runningMutex;
    std::mutex isHashEmptyMutex;
    std::mutex hashFoundMutex;
    std::condition_variable condition;

    /**
     * Generates hash.
     *
     * @param wordToHash The word to hash.
     * @return The hash value of the given word.
     */
    const std::string hashWord(const char*, char*);
};


#endif //UNSHA_ME_HASHPRODUCER_H
