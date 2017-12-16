#include "../include/threaded-bruteforce.hpp"

ThreadedBruteforce::ThreadedBruteforce(
        const uint8_t nbThreads,
        std::string hashedPass,
        Bruteforce* bruteforce
) :
        nbThreads(nbThreads),
        mutex(),
        cv(),
        hashedPass(hashedPass),
        foundHash(false),
        bruteforce(bruteforce) {
//    for (uint8_t i = 1; i <= nbThreads; ++i) {
//        bruteforcers.emplace_front(std::thread(
//                &ThreadedBruteforce::threadedBruteforcer,
//                this, i
//        ));
//    }
}

//ThreadedBruteforce::~ThreadedBruteforce() {
//    for (uint8_t i = 0; i < nbThreads; ++i) {
//        bruteforcers[i].join();
//    }
//}

void ThreadedBruteforce::threadedBruteforcer(const uint8_t id) {
    Logger log;

    log.info(std::stringstream() << "=> thread id : " << std::to_string(id));

    /*std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [&]() {
       return !foundHash;
    });*/

    for (uint8_t wordLength = id; wordLength < MAX_WORD_SIZE; wordLength += nbThreads) {

        double start = omp_get_wtime();

        bool result = bruteforce->startBruteforceByWordLength(wordLength);

        double end = omp_get_wtime();

        log.info(std::stringstream() << "Word Len : " << std::to_string(wordLength));
        log.info(std::stringstream() << "Executed Time : " << end - start);

        if (result) {
//            log.info(std::stringstream() << "Result Password : " << result);

            foundHash = true;
            bruteforce->notifyHashFound();
//            cv.notify_all();
            break;
        }
    }
}

//std::deque<std::thread> &ThreadedBruteforce::getBruteforcers() {
//    return bruteforcers;
//}

const uint8_t ThreadedBruteforce::getNbThreads() const {
    return nbThreads;
}
