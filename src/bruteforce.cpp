#include "../include/bruteforce.hpp"

Bruteforce::Bruteforce(std::string hash) :
        hashedPassword(std::move(hash)), shouldStop(false) {}

bool Bruteforce::startBruteforceByWordLength(uint8_t length) {
    std::vector<uint8_t> indexesVector(length, 0);
    SHA256_CTX sha256{};

    SHA256_Init(&sha256);

    while (!shouldStop) {
        auto generatedWord = static_cast<char *>(malloc(indexesVector.size()));

        for (uint8_t i = 0; i < indexesVector.size(); ++i) {
            generatedWord[i] = alphabet[indexesVector[i]];
        }

        if (isSearchedSHA256Hash(&generatedWord, sha256)) {
            std::cout << std::string(generatedWord) << std::endl;
            return true;
        }

        for (unsigned long i = indexesVector.size() - 1;; --i) {

            if (i < 0) {
                return false;
            }

            ++indexesVector[i];

            if (indexesVector[i] == strlen(alphabet))
                indexesVector[i] = 0;
            else
                break;
        }

        if (generatedWord != nullptr) {
            free(generatedWord);
        }
    }
    return false;
}

inline bool Bruteforce::isSearchedSHA256Hash(char **wordToHash, SHA256_CTX &sha256) {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    std::stringstream hashedWord;

    SHA256_Update(&sha256, *wordToHash, strlen(*wordToHash));
    SHA256_Final(hash, &sha256);

    for (uint8_t i : hash) {
        hashedWord << std::hex << std::setw(2) << std::setfill('0') << (int) i;
    }

    return hashedWord.str() == hashedPassword;
}

void Bruteforce::notifyHashFound() {
    shouldStop = true;
}

Bruteforce::~Bruteforce() {
//    delete [] alphabet;
//    std::cout << "destroying brute force" << std::endl;
}
