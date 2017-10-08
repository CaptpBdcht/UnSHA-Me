#include "../include/bruteforce.hpp"
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
            this,
            i
        ));
    }
}

ThreadedBruteforce::~ThreadedBruteforce()
{
    for (uint8_t i = 0; i < nbThreads; ++i)
        bruteforcers[i].join();
}

void ThreadedBruteforce::threadedBruteforcer(const uint8_t id)
{
    Logger log;

    log.info(std::stringstream() << "=> thread id : " << std::to_string(unsigned(id)));
    
    Bruteforce bruteforce(hashedPass);
    
    for (uint8_t len = id; len < MAX_SIZE; len += nbThreads) {
        bruteforce.startBruteforce(len);
    }

    {
        std::lock_guard<std::mutex> lock(mutex);
        log.info(std::stringstream() << "<= thread id : " << std::to_string(unsigned(id)));
        cv.notify_all();
    }
}