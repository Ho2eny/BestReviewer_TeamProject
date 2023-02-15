#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <time.h>

#define MAX_COUNT 2
#define MAX_LENGTH 8
typedef long long ll;
using namespace std;

class AuthorizationKey {
public:
    AuthorizationKey();
    void SetId(const string& param) { id_.assign(param); };
    void SetPassword(const string& param);
    string QueryPassword();
    string QueryPasswordWithNonce();
    string QueryNonce() { return nonce_; };
private:
    string id_, password_, nonce_;
    ll GenerateHash(const string& str);
    void UpdateNonceKey();
};

AuthorizationKey::AuthorizationKey() {
    srand((unsigned int)time(0));
    UpdateNonceKey();
}

void AuthorizationKey::SetPassword(const string& param) {
    password_.assign(param);
    UpdateNonceKey();
}

void AuthorizationKey::UpdateNonceKey() {
    nonce_.assign(to_string(rand() % 9));
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