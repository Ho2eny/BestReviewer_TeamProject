#ifndef CONNECION_FAILURE_EXCEPTION_H_
#define CONNECION_FAILURE_EXCEPTION_H_

#include "../../../common/exception/base_exception.h"

class ConnectionFailureException : public BaseException {
public:
  ConnectionFailureException(const char* message) : BaseException(message) {}
};

#endif 