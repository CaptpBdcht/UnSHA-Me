#ifndef UNSHA_ME_HASH_H
#define UNSHA_ME_HASH_H

#include <openssl/md5.h>
#include <ostream>
#include <unordered_map>

class Hash {
public:
    Hash();

    Hash(const std::string &password);

    bool operator==(const Hash &other) const;

    static Hash storeHash(const std::string &passwordHash);

    friend std::ostream &operator<<(std::ostream &output, const Hash &input);

    friend struct HashMapFunctor;
private:
    uint64_t hash[2];
};

struct HashMapFunctor //funktor hashujacy Hashe dla tablicy hashujacej #incepcja
{
    size_t operator()(const Hash &h) const {
        return h.hash[0] xor h.hash[1];
    }
};

typedef std::unordered_multimap<Hash, std::string, HashMapFunctor> PasswordMap;

std::string &toLower(std::string &str);

std::string &toUpper(std::string &str);


#endif //UNSHA_ME_HASH_H
