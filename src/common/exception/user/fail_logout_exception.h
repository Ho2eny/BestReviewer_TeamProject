#ifndef FAIL_LOGOUT_EXCEPTION_H_
#define FAIL_LOGOUT_EXCEPTION_H_

#include "../base_exception.h"

class FailLogoutException : public BaseException {
public:
  FailLogoutException(const char* message) : BaseException(message) {}
};

#endif 