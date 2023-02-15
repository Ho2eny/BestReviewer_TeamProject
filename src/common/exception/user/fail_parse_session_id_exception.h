#ifndef FAIL_PARSE_SESSION_ID_EXCEPTION_H_
#define FAIL_PARSE_SESSION_ID_EXCEPTION_H_

#include "../base_exception.h"

class FailParseSessionIdException : public BaseException {
public:
  FailParseSessionIdException(const char* message) : BaseException(message) {}
};

#endif 