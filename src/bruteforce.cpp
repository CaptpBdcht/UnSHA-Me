#include "../include/bruteforce.hpp"

Bruteforce::Bruteforce(std::string hash) :
    hashedPassword(std::move(hash)) {}

void Bruteforce::startBruteforce(uint8_t wordLen) {

    Logger log;

    double start = omp_get_wtime();

    log.info(std::stringstream() << std::to_string(wordLen));

    std::string searchPassword = checkGeneratedWordsByLength(alphabet, wordLen);

    if (!searchPassword.empty())
        log.info(std::stringstream() << searchPassword);

    double end = omp_get_wtime();

    log.info(std::stringstream() << "Word Len : " << std::to_string(unsigned(wordLen)));
    log.info(std::stringstream() << "Executed Time : " << end - start);
}

inline std::string Bruteforce::checkGeneratedWordsByLength(const char *alphabet, uint8_t length) {

    std::vector<uint8_t> indexesVector(length, 0);
    SHA256_CTX sha256;

    SHA256_Init(&sha256);

    while (true) {

        std::string generatedWord(indexesVector.size(), ' ');

        for (uint8_t i = 0; i < indexesVector.size(); ++i) {
            generatedWord[i] = alphabet[indexesVector[i]];
        }

        if (isSearchedSHA256Hash(generatedWord, sha256)) {
            return generatedWord;
        }

        for (long i = indexesVector.size() - 1;; --i) {

            if (i < 0)
                return "";

            ++indexesVector[i];

            if (indexesVector[i] == strlen(alphabet))
                indexesVector[i] = 0;
            else
                break;
        }
    }
}

inline bool Bruteforce::isSearchedSHA256Hash(const std::string &wordToHash, SHA256_CTX sha256) {

    uint8_t hash[SHA256_DIGEST_LENGTH];
    std::stringstream hashedWord;

    SHA256_Update(&sha256, wordToHash.c_str(), wordToHash.size());
    SHA256_Final(hash, &sha256);

    for (uint8_t i : hash) {
        hashedWord << std::hex << std::setw(2) << std::setfill('0') << (int) i;
    }

    return hashedWord.str() == hashedPassword;
}