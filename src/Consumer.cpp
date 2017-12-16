#include <utility>
#include <iostream>

#include "../include/Consumer.h"

using namespace std;

Consumer::Consumer(string hashedWord, HashProducer *hashProducer)
        : hashedWord(move(hashedWord)), hashProducer(hashProducer) {}

bool Consumer::isExpectedHash(const string &hash) {
    return hash == hashedWord;
}

void Consumer::startConsuming() {
//     cout << "startConsuming..." << endl;
    while (hashProducer->isRunning()) {
//        cout << "is running..." << endl;
        while (hashProducer->isHashAvailable()) {
//             cout << "is available..." << endl;
            const string hash = hashProducer->consumeWord();
            if (isExpectedHash(hash)) {
                // TODO: Notify Producer that hash has been found.
                hashProducer->notifyHashFound(true, hash);
                cout << "FOUND..." << endl;
            } else {
//                cout << "no match..." << endl;
            }
        }
//        hashProducer->notifyHashFound(false, "");
    }
}
