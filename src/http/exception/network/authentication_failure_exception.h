#ifndef AUTHENTICATION_FAILURE_H_
#define AUTHENTICATION_FAILURE_H_

#include "../../../common/exception/base_exception.h"

class AuthenticationFailureException : public BaseException {
public:
  AuthenticationFailureException(const char* message) : BaseException(message) {}
};

#endif 