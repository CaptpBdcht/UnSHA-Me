#include <algorithm>
#include <iomanip>
#include <iostream>
#include "../include/HashProducer.h"

using namespace std;

HashProducer::HashProducer(const std::string alphabet) : alphabet(alphabet), shouldStop(false) {
}

void HashProducer::startWordGeneration() {
    sort(alphabet.begin(), alphabet.end());
    do {
        char mdString[SHA256_DIGEST_LENGTH * 2 + 1];
        const string result = hashWord(alphabet.c_str(), mdString);
        generatedHashesMap.insert(make_pair(result, alphabet));
        generatedHashes.push_back(result);
//        cout << "<" << alphabet << "," << result << ">" << endl;
    } while (next_permutation(alphabet.begin(), alphabet.end()));
    while (!isHashAvailable()) {}
    shouldStop = true;
}

bool HashProducer::isHashAvailable() {
//    isHashEmptyMutex.lock();
    const bool isAvailable = !generatedHashes.empty();
//    isHashEmptyMutex.unlock();

    return isAvailable;
}

bool HashProducer::isRunning() {
//    runningMutex.lock();
    const bool isRunning = !shouldStop;
//    runningMutex.unlock();
//    condition.wait(lock); // release lock and go join the waiting thread queue
    return isRunning;
}

const string HashProducer::consumeWord() {
    mutex.lock();
    const string word = generatedHashes.front();
    generatedHashes.pop_front();
    mutex.unlock();
    return word;
}

const string HashProducer::hashWord(const char *wordToHash, char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];

    SHA256_CTX ctx{};
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, wordToHash, strlen(wordToHash));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&output[i * 2], "%02x", (unsigned int) digest[i]);
    }

    return output;
}

void HashProducer::notifyHashFound(bool hashFound, const std::string hash) {
    hashFoundMutex.lock();
    if (hashFound && generatedHashesMap.find(hash) != generatedHashesMap.end()) {
        cout << generatedHashesMap[hash] << endl;
    }
    shouldStop = true;
    hashFoundMutex.unlock();
}
