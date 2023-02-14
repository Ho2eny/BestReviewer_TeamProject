#include <sstream>
#include <random>

using namespace std;

string GetHashCode(const string &password)
{
    long long hash = 5381;
    int c;
    const char *c_str = password.c_str();
    while (c = *c_str++)
    {
        hash = (((hash << 5) + hash) + c) % 1000000007;
    }
    long long result = hash % 1000000007;

    stringstream stream;
    stream << result;
    return stream.str();
}

string GetNonce()
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist9(1, 9);
    return to_string(dist9(rng));
}

string GetPasswordWithNonce(const string &password, const string &nonce)
{
    string new_password = GetHashCode(password);
    return GetHashCode(new_password + nonce);
}