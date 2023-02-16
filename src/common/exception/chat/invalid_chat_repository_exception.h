#ifndef INVALID_CHAT_REPOSITORY_EXCEPTION_H_
#define INVALID_CHAT_REPOSITORY_EXCEPTION_H_

#include "../base_exception.h"

class InvalidChatRepositoryException : public BaseException {
public:
  InvalidChatRepositoryException(const char* message) : BaseException(message) {}
};

#endif 