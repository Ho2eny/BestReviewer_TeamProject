#ifndef FAIL_PARSE_RETRIEVE_ROOM_RESPONSE_EXCEPTION_H_
#define FAIL_PARSE_RETRIEVE_ROOM_RESPONSE_EXCEPTION_H_

#include "../base_exception.h"

class FailParseRetrieveRoomResponseException : public BaseException {
public:
  FailParseRetrieveRoomResponseException(const char* message) : BaseException(message) {}
};

#endif 