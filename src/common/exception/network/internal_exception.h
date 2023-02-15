#ifndef INTERNAL_EXCEPTION_H_
#define INTERNAL_EXCEPTION_H_

#include "../base_exception.h"

class InternalException : public BaseException {
public:
  InternalException(const char* message) : BaseException(message) {}
};

#endif 