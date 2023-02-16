#ifndef INVALID_ID_PASSWORD_EXCEPTION_H_
#define INVALID_ID_PASSWORD_EXCEPTION_H_

#include "../base_exception.h"

class InvalidIdPasswordException : public BaseException {
public:
  InvalidIdPasswordException(const char* message) : BaseException(message) {}
};

#endif 