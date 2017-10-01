#include "../include/bruteforce.hpp"

Bruteforce::Bruteforce(int threadsNumber, std::string hash) :
    nbThreads(threadsNumber), 
    hashedPassword(std::move(hash)) {}

void Bruteforce::startBruteforce() {

    Logger log;
    //volatile bool endMultiThreadLoop = false;

    omp_set_num_threads(nbThreads);

    double start = omp_get_wtime();

    //#pragma omp parallel for shared(endMultiThreadLoop)
    for (uint8_t i = minPassLength; i <= maxPassLength; ++i) {

        //if (endMultiThreadLoop)
        //    continue;

        std::string searchPassword = checkGeneratedWordsByLength(alphabet, i);

        if (!searchPassword.empty()) {
            log.info(std::stringstream() << searchPassword);
            break;
            //endMultiThreadLoop = true;
        }
    }

    double end = omp_get_wtime();

    log.info(std::stringstream() << "Executed Time : " << end - start);
}

std::string Bruteforce::checkGeneratedWordsByLength(const char *alphabet, uint8_t length) {

    std::vector<uint8_t> indexesVector(length, 0);
    //std::string searchWord;

    while (true) {

        std::string generatedWord(indexesVector.size(), ' ');

        for (uint8_t i = 0; i < indexesVector.size(); ++i)
            generatedWord[i] = alphabet[indexesVector[i]];

        if (isSearchedSHA256Hash(generatedWord)) {
            //searchWord = generatedWord;
            //endMultiThreadLoop = true;
            return generatedWord;
        }

        for (long i = indexesVector.size() - 1;; --i) {

            if (i < 0)
                return "";
                //endMultiThreadLoop = true;

            ++indexesVector[i];

            if (indexesVector[i] == strlen(alphabet))
                indexesVector[i] = 0;
            else
                break;
        }
    }

    //return searchWord;
}

bool Bruteforce::isSearchedSHA256Hash(const std::string &wordToHash) {

    std::string hashedWord;

    picosha2::hash256_hex_string(wordToHash, hashedWord);

    return hashedWord == hashedPassword;
}