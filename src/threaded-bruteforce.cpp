#include "../include/threaded-bruteforce.hpp"

ThreadedBruteforce::ThreadedBruteforce(
    const uint8_t nbThreads,
    const std::string hashedPass
) :
    nbThreads(nbThreads),
    bruteforcers(nbThreads),
    mutex(),
    cv(),
    hashedPass(hashedPass),
    foundHash(false)
{
    for (uint8_t i = 1; i <= nbThreads; ++i) {
        bruteforcers.emplace_front(std::thread(
            &ThreadedBruteforce::threadedBruteforcer,
            this, i
        ));
    }
}

ThreadedBruteforce::~ThreadedBruteforce()
{
    for (uint8_t i = 0; i < nbThreads; ++i) {
        bruteforcers[i].join();
    }
}

void ThreadedBruteforce::threadedBruteforcer(const uint8_t id)
{
    Logger log;

    log.info(std::stringstream() << "=> thread id : " << std::to_string(id));

    /*std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [&]() {
       return !foundHash;
    });*/

    for (uint8_t wordLength = id; wordLength < MAX_WORD_SIZE; wordLength += nbThreads) {

        double start = omp_get_wtime();

        std::string result = startBruteforceByWordLength(wordLength);

        double end = omp_get_wtime();

        log.info(std::stringstream() << "Word Len : " << std::to_string(wordLength));
        log.info(std::stringstream() << "Executed Time : " << end - start);

        if (!result.empty()) {
            log.info(std::stringstream() << "Result Password : " << result);

            foundHash = true;
            cv.notify_all();
            break;
        }
    }
}

std::string ThreadedBruteforce::startBruteforceByWordLength(uint8_t length) {

    std::vector<uint8_t> indexesVector(length, 0);
    SHA256_CTX sha256;

    SHA256_Init(&sha256);

    while (true) {

        char *generatedWord = static_cast<char *>(malloc(indexesVector.size()));

        for (uint8_t i = 0; i < indexesVector.size(); ++i) {
            generatedWord[i] = alphabet[indexesVector[i]];
        }

        if (isSearchedSHA256Hash(&generatedWord, sha256)) {
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

        if (generatedWord != nullptr) {
            free(generatedWord);
        }
    }
}

inline bool ThreadedBruteforce::isSearchedSHA256Hash(char **wordToHash, SHA256_CTX sha256) {

    uint8_t hash[SHA256_DIGEST_LENGTH];
    std::stringstream hashedWord;

    SHA256_Update(&sha256, *wordToHash, strlen(*wordToHash));
    SHA256_Final(hash, &sha256);

    for (uint8_t i : hash) {
        hashedWord << std::hex << std::setw(2) << std::setfill('0') << (int) i;
    }

    return hashedWord.str() == hashedPass;
}