#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <mutex>

class Logger {

public:
    void info(const std::ostream &, std::string prefix = "[INFO] ");
    void debug(const std::ostream &);
    void error(const std::ostream &);

private:
    std::mutex mutex;
};

#endif