#ifndef UNSHA_ME_HASHPRODUCER_H
#define UNSHA_ME_HASHPRODUCER_H

#include <condition_variable>
#include <cstring>
#include <deque>
#include <mutex>
#include <string>
#include <sstream>
#include <vector>

#include "sha.h"
#include "HashConsumer.h"

/** Simple class that generates a hash. */
class HashProducer {
public:
    explicit HashProducer(std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");

    /** Generates all anagram of the current alphabet. */
    void startWordGeneration();
    const std::string& consumeWord();
private:
    std::string alphabet;
    std::vector<HashConsumer> consumers;
    std::deque<std::string> generatedHashes;
    std::mutex mutex;
    std::condition_variable condition;
    SHA256_CTX sha256;
    /**
     * Generates hash.
     *
     * @param wordToHash The word to hash.
     * @return The hash value of the given word.
     */
    const std::string hashWord(char **wordToHash);
};


#endif //UNSHA_ME_HASHPRODUCER_H
