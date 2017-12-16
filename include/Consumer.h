#ifndef UNSHA_ME_CONSUMER_H
#define UNSHA_ME_CONSUMER_H

#include <string>
#include "HashProducer.h"

class Consumer {
public:
    explicit Consumer(std::string hashedWord, HashProducer *hashProducer);

    bool isExpectedHash(const std::string&);

    void startConsuming();

    virtual ~Consumer() = default;

private:
    const std::string hashedWord;
    HashProducer *hashProducer;
};

#endif //UNSHA_ME_CONSUMER_H
