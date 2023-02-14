#ifndef UTIL_H_
#define UTIL_H_
#include <string>

std::string GetHashCode(const std::string &password);
std::string GetNonce();
std::string GetPasswordWithNonce(const std::string &password, const std::string &nounce);

#endif