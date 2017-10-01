#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <mutex>

class Logger {

public:
    void info(const std::ostream &stream, std::string prefix = "[INFO] ");
    void debug(const std::ostream &stream);
    void error(const std::ostream &stream);

private:
    std::mutex mutex;
};

#endif