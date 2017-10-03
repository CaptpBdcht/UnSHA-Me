#include "../include/bruteforce.hpp"

Bruteforce::Bruteforce(int threadsNumber, std::string hash) :
    nbThreads(threadsNumber), 
    hashedPassword(std::move(hash)) {}

void Bruteforce::startBruteforce() {

    Logger log;
    omp_set_num_threads(nbThreads);

    double start = omp_get_wtime();

    for (uint8_t i = minPassLength; i <= maxPassLength; ++i) {
        log.info(std::stringstream() << std::to_string(i));

        std::string searchPassword = checkGeneratedWordsByLength(alphabet, i);

        if (!searchPassword.empty()) {
            log.info(std::stringstream() << searchPassword);
            break;
        }
    }

    double end = omp_get_wtime();

    log.info(std::stringstream() << "Executed Time : " << end - start);
}

std::string Bruteforce::checkGeneratedWordsByLength(const char *alphabet, uint8_t length) {

    std::vector<uint8_t> indexesVector(length, 0);

    while (true) {

        std::string generatedWord(indexesVector.size(), ' ');

        for (uint8_t i = 0; i < indexesVector.size(); ++i)
            generatedWord[i] = alphabet[indexesVector[i]];

        if (isSearchedSHA256Hash(generatedWord)) {
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

bool Bruteforce::isSearchedSHA256Hash(const std::string &wordToHash) {

    unsigned char hash[SHA256_DIGEST_LENGTH];
    std::stringstream hashedWord;
    SHA256_CTX sha256;

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, wordToHash.c_str(), wordToHash.size());
    SHA256_Final(hash, &sha256);

    for (unsigned char i : hash) {
        hashedWord << std::hex << std::setw(2) << std::setfill('0') << (int) i;
    }

    return hashedWord.str() == hashedPassword;
}