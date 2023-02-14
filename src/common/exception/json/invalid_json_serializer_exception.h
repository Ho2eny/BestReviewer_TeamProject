#ifndef INVALID_JSON_SERIALIZER_EXCEPTION_H_
#define INVALID_JSON_SERIALIZER_EXCEPTION_H_

#include "common/exception/base_exception.h"

class InvalidJsonSerializerException : public BaseException {
public:
  InvalidJsonSerializerException(const char* message) : BaseException(message) {}
};

#endif 