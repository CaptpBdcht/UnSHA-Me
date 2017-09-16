#include "../include/logger.hpp"

void Logger::info(const std::ostream &stream) {
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << stream.rdbuf() << std::endl;
}

void Logger::debug(const std::ostream &stream) {
    #ifndef NDEBUG
        Logger::info(stream);
    #endif
}

void Logger::error(const std::ostream &stream) {
    std::lock_guard<std::mutex> lock(mutex);
    std::cerr << stream.rdbuf() << std::endl;
}