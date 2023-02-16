#ifndef FAIL_THREAD_ATTR_INIT_EXCEPTION_H_
#define FAIL_THREAD_ATTR_INIT_EXCEPTION_H_

#include "../base_exception.h"

class FailThreadAttrInitException : public BaseException {
public:
  FailThreadAttrInitException(const char* message) : BaseException(message) {}
};

#endif 