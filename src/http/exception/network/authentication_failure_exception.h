#ifndef AUTHENTICATION_FAILURE_H_
#define AUTHENTICATION_FAILURE_H_

#include "base_network_exception.h"

class AuthenticationFailureException : public BaseNetworkException {
public:
  AuthenticationFailureException(const char* message) : BaseNetworkException(message) {}
};

#endif 