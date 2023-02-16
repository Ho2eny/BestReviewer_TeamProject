#ifndef INVALID_USER_REPOSITORY_EXCEPTION_H_
#define INVALID_USER_REPOSITORY_EXCEPTION_H_

#include "../base_exception.h"

class InvalidUserRepositoryException : public BaseException {
public:
  InvalidUserRepositoryException(const char* message) : BaseException(message) {}
};

#endif 