#ifndef INVALID_JSON_STRING_EXCEPTION_H_
#define INVALID_JSON_STRING_EXCEPTION_H_

#include "base_json_exception.h"

class InvalidJsonStringException : public BaseJsonException {
public:
  InvalidJsonStringException(const char* message) : BaseJsonException(message) {}
};

#endif 