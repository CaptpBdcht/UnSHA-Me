#include "Hash.h"

uint64_t swapBytes(const uint64_t &input) {
#ifdef __GNUG__
    return __builtin_bswap64(input);
#elif _MSC_VER
    return _byteswap_uint64(input);
#endif
}

Hash::Hash() {
    hash[0] = 0;
    hash[1] = 0;
}

Hash::Hash(const std::string &password) {
    MD5(reinterpret_cast<const unsigned char *>(password.c_str()),
        password.length(),
        reinterpret_cast<unsigned char *>(hash));
}

bool Hash::operator==(const Hash &other) const {
    return hash[0] == other.hash[0] && hash[1] == other.hash[1];
}

Hash Hash::storeHash(const std::string &passwordHash) {
    Hash ret;
    auto mostSignificantBytes = passwordHash.substr(0, 16);
    auto leastSignificantBytes = passwordHash.substr(16);

    ret.hash[0] = swapBytes(std::stoull(mostSignificantBytes, nullptr, 16));
    ret.hash[1] = swapBytes(std::stoull(leastSignificantBytes, nullptr, 16));
    return ret;
}

std::ostream &operator<<(std::ostream &output, const Hash &input) {
    output << std::hex << swapBytes(input.hash[0]);
    output << std::hex << swapBytes(input.hash[1]);
    return output;
}

std::string &toUpper(std::string &str) {
    for (auto &c : str) {
        c = std::toupper(c);
    }
    return str;
}

std::string &toLower(std::string &str) {
    for (auto &c : str) {
        c = std::tolower(c);
    }
    return str;
}