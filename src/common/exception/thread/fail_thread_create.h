#ifndef FAIL_THREAD_CREATE_EXCEPTION_H_
#define FAIL_THREAD_CREATE_EXCEPTION_H_

#include "../base_exception.h"

class FailThreadCreateException : public BaseException {
public:
  FailThreadCreateException(const char* message) : BaseException(message) {}
};

#endif 