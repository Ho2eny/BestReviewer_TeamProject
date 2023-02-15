#ifndef FAIL_RETRIEVE_ROOM_EXCEPTION_H_
#define FAIL_RETRIEVE_ROOM_EXCEPTION_H_

#include "../base_exception.h"

class FailRetrieveRoomException : public BaseException {
public:
  FailRetrieveRoomException(const char* message) : BaseException(message) {}
};

#endif 