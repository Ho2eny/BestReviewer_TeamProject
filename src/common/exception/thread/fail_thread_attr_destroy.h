#ifndef FAIL_THREAD_ATTR_DESTROY_EXCEPTION_H_
#define FAIL_THREAD_ATTR_DESTROY_EXCEPTION_H_

#include "../base_exception.h"

class FailThreadAttrDestroyException : public BaseException {
public:
  FailThreadAttrDestroyException(const char* message = "pthread_attr_destroy is failed") : BaseException(message) {}
};

#endif
