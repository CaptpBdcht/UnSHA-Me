#include <algorithm>
#include <iomanip>
#include <iostream>
#include "../include/HashProducer.h"

using namespace std;

HashProducer::HashProducer(const std::string alphabet) : alphabet(alphabet) {
    SHA256_Init(&sha256);
}

void HashProducer::startWordGeneration() {
    sort(alphabet.begin(), alphabet.end());
    do {
        auto anagram = new char[alphabet.length() + 1];
        strcpy(anagram, alphabet.c_str());

        const string result = hashWord(&anagram);
        generatedHashes.push_back(result);
        cout << result << endl;
    } while (next_permutation(alphabet.begin(), alphabet.end()));
}

const string &HashProducer::consumeWord() {
    unique_lock <std::mutex> lock(mutex);
    const string word = generatedHashes.front();
    condition.wait(lock); // release lock and go join the waiting thread queue
    return word;
}

const string HashProducer::hashWord(char **wordToHash) {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    std::stringstream hashedWord;

    SHA256_Update(&sha256, *wordToHash, strlen(*wordToHash));
    SHA256_Final(hash, &sha256);

    for (uint8_t i : hash) {
        hashedWord << std::hex << std::setw(2) << std::setfill('0') << (int) i;
    }

    return hashedWord.str();
}
