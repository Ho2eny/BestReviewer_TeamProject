#ifndef FAIL_SEND_MESSAGE_EXCEPTION_H_
#define FAIL_SEND_MESSAGE_EXCEPTION_H_

#include "../base_exception.h"

class FailSendMessageException : public BaseException {
public:
  FailSendMessageException(const char* message) : BaseException(message) {}
};

#endif 