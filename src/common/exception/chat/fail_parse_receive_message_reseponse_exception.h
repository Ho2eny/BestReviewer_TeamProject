#ifndef FAIL_PARSE_RECEIVE_MESSAGE_RESPONSE_EXCEPTION_H_
#define FAIL_PARSE_RECEIVE_MESSAGE_RESPONSE_EXCEPTION_H_

#include "../base_exception.h"

class FailParseReceiveMessageResponseException : public BaseException {
public:
  FailParseReceiveMessageResponseException(const char* message) : BaseException(message) {}
};

#endif 