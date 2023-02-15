#ifndef INVALID_COMMAND_EXCEPTION_H_
#define INVALID_COMMAND_EXCEPTION_H_

#include "../base_exception.h"

class InvalidCommandException : public BaseException
{
public:
  InvalidCommandException(const char *message = "Command is invalid.")
      : BaseException(message) {}
};

#endif
