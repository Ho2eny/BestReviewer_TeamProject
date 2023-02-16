#ifndef INVALID_JSON_SERIALIZER_EXCEPTION_H_
#define INVALID_JSON_SERIALIZER_EXCEPTION_H_

#include "base_json_exception.h"

class InvalidJsonSerializerException : public BaseJsonException {
public:
  InvalidJsonSerializerException(const char* message) : BaseJsonException(message) {}
};

#endif 