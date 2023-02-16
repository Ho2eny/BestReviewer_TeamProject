#ifndef INVALID_ROOM_REPOSITORY_EXCEPTION_H_
#define INVALID_ROOM_REPOSITORY_EXCEPTION_H_

#include "../base_exception.h"

class InvalidRoomRepositoryException : public BaseException {
public:
  InvalidRoomRepositoryException(const char* message) : BaseException(message) {}
};

#endif 