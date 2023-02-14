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
    void setId(const string& param) { id_.assign(param); };
    void setPassword(const string& param) { password_.assign(param); }
    string queryPassword();
    string queryPasswordWithNonce();
    string queryNonce() { return nonce_; };
private:
    string id_, password_, nonce_;
    ll generateHash(const string& str);
};

AuthorizationKey::AuthorizationKey() {
    srand((unsigned int)time(0));
    //  temp  0~9 사이의 임의의 한자리 수   
    nonce_.assign(to_string(rand() % 9));
}

ll AuthorizationKey::generateHash(const string& str) {
    ll hash = 5381;
    int c;
    const char *c_str = str.c_str();
    while(c = *c_str++)
        hash = ((( hash << 5 ) + hash) + c) % 1000000007;
    return hash % 1000000007;
}

string AuthorizationKey::queryPassword() {
    return to_string(generateHash(password_));
}

string AuthorizationKey::queryPasswordWithNonce() {
    return to_string(generateHash( std::to_string(generateHash(password_)) + nonce_));
}

#endif