#include "utils.h"

void AuthorizationKey::UpdateNonceKey()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 9);
    nonce_.assign(to_string(distrib(gen)));
}

ll AuthorizationKey::GenerateHash(const string &str)
{
    ll hash = 5381;
    int c;
    const char *c_str = str.c_str();
    while (c = *c_str++)
        hash = (((hash << 5) + hash) + c) % 1000000007;
    return hash % 1000000007;
}

string AuthorizationKey::QueryPassword()
{
    return to_string(GenerateHash(password_));
}

string AuthorizationKey::QueryPasswordWithNonce()
{
    return to_string(GenerateHash(std::to_string(GenerateHash(password_)) + nonce_));
}