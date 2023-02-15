#ifndef INVALID_JSON_STRING_EXCEPTION_H_
#define INVALID_JSON_STRING_EXCEPTION_H_

#include "../../../../common/exception/base_exception.h"

class InvalidJsonStringException : public BaseException {
public:
  InvalidJsonStringException(const char* message) : BaseException(message) {}
};

#endif 