#include <sstream>
#include "../include/logger.hpp"
#include "../include/thread_pool.hpp"

int main(int argc, char **argv) {
    Logger log;
    ThreadPool threadPool(5);

    log.info(std::stringstream() << "test");

    return EXIT_SUCCESS;
}