#ifndef INVALID_PARAMETER_EXCEPTION_H_
#define INVALID_PARAMETER_EXCEPTION_H_

#include "../base_exception.h"

class InvalidParameterException : public BaseException
{
public:
  InvalidParameterException(const char *message) : BaseException(message) {}
};

#endif
