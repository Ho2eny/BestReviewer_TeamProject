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
#endif