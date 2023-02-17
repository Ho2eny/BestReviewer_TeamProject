#ifndef FAIL_RECEIVE_MESSAGE_EXCEPTION_H_
#define FAIL_RECEIVE_MESSAGE_EXCEPTION_H_

#include "../base_exception.h"

class FailReceiveMessageException : public BaseException {
public:
  FailReceiveMessageException(const char* message) : BaseException(message) {}
};

#endif 