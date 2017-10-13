#include "../include/threaded-bruteforce.hpp"

ThreadedBruteforce::ThreadedBruteforce(
    const uint8_t nbThreads,
    const std::string hashedPass
) :
    nbThreads(nbThreads),
    bruteforcers(nbThreads),
    mutex(),
    cv(),
    hashedPass(hashedPass)
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
    
    Bruteforce bruteforce(hashedPass);
    
    for (uint8_t wordLength = id; wordLength < MAX_WORD_SIZE; wordLength += nbThreads) {

        double start = omp_get_wtime();

        std::string result = bruteforce.startBruteforceByWordLength(wordLength);

        double end = omp_get_wtime();

        log.info(std::stringstream() << "Word Len : " << std::to_string(wordLength));
        log.info(std::stringstream() << "Executed Time : " << end - start);

        if (!result.empty()) {
            log.info(std::stringstream() << "Result Password : " << result);
            break;
        }
    }
}