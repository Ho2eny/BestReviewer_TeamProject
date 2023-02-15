#ifndef FAIL_CREATE_ROOM_EXCEPTION_H_
#define FAIL_CREATE_ROOM_EXCEPTION_H_

#include "../base_exception.h"

class FailCreateRoomException : public BaseException {
public:
  FailCreateRoomException(const char* message) : BaseException(message) {}
};

#endif 