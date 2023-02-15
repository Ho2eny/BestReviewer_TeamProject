#ifndef FAIL_LOGIN_EXCEPTION_H_
#define FAIL_LOGIN_EXCEPTION_H_

#include "../base_exception.h"

class FailLoginException : public BaseException {
public:
  FailLoginException(const char* message) : BaseException(message) {}
};

#endif 