#ifndef FAIL_THREAD_JOIN_EXCEPTION_H_
#define FAIL_THREAD_JOIN_EXCEPTION_H_

#include "../base_exception.h"

class FailThreadJoinException : public BaseException {
public:
  FailThreadJoinException(const char* message) : BaseException(message) {}
};

#endif 