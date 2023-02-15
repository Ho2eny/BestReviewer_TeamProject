#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <time.h>
#include <random>

typedef long long ll;
using namespace std;

class AuthorizationKey {
public:
    AuthorizationKey(const string& id_arg, const string& password_arg) : 
        id_(id_arg), password_(password_arg) {        
        UpdateNonceKey();
    }

    string QueryPassword();
    string QueryPasswordWithNonce();
    string QueryNonce() { return nonce_; };
private:
    string id_, password_, nonce_;
    ll GenerateHash(const string& str);
    void UpdateNonceKey();
};

void AuthorizationKey::UpdateNonceKey() {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, 9);
    nonce_.assign(to_string(distrib(gen)));
}

ll AuthorizationKey::GenerateHash(const string& str) {
    ll hash = 5381;
    int c;
    const char *c_str = str.c_str();
    while(c = *c_str++)
        hash = ((( hash << 5 ) + hash) + c) % 1000000007;
    return hash % 1000000007;
}

string AuthorizationKey::QueryPassword() {
    return to_string(GenerateHash(password_));
}

string AuthorizationKey::QueryPasswordWithNonce() {
    return to_string(GenerateHash( std::to_string(GenerateHash(password_)) + nonce_));
}

#endif