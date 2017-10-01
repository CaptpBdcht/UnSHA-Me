#include "../include/logger.hpp"

void Logger::info(const std::ostream &stream, const std::string prefix) {
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << prefix << stream.rdbuf() << std::endl;
}

void Logger::debug(const std::ostream &stream) {
    #ifndef NDEBUG
        info(stream, "[DEBUG] ");
    #endif
}

void Logger::error(const std::ostream &stream) {
    std::lock_guard<std::mutex> lock(mutex);
    std::cerr << "[ERROR] " << stream.rdbuf() << std::endl;
}