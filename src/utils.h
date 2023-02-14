#include <iostream>
#include <string>
#include <time.h>

#define MAX_COUNT 2
#define MAX_LENGTH 8
typedef long long ll;
using namespace std;

class AuthorizationKey {
public:
    void setId(const string& param) { id.assign(param); };
    void setPassword(const string& param) { password.assign(param); }
    ll queryPassword();
private:
    string id, password, nonce;
    ll generateHash(const string& str);
};

long long AuthorizationKey::generateHash(const string& str) {
    long long hash = 5381;
    int c;
    const char *c_str = str.c_str();
    while(c = *c_str++) {
        hash = ((( hash <<5 ) + hash) + c) % 1000000007;
    }
    return hash % 1000000007;
}

ll AuthorizationKey::queryPassword() {
    ll ret = 0;
    string temp;
    srand((unsigned int)time(0));

    //  temp  0~9 사이의 임의의 한자리 수   
    nonce.assign(to_string(rand() % 9));
    ret = generateHash( std::to_string(generateHash(password)) + nonce);
    return ret;
}

