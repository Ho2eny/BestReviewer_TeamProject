#ifndef FAIL_SIGNUP_EXCEPTION_H_
#define FAIL_SIGNUP_EXCEPTION_H_

#include "../base_exception.h"

class FailSignupException : public BaseException {
public:
  FailSignupException(const char* message) : BaseException(message) {}
};

#endif 