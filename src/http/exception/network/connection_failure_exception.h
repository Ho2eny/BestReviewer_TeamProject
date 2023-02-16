#ifndef CONNECION_FAILURE_EXCEPTION_H_
#define CONNECION_FAILURE_EXCEPTION_H_

#include "base_network_exception.h"

class ConnectionFailureException : public BaseNetworkException {
public:
  ConnectionFailureException(const char* message) : BaseNetworkException(message) {}
};

#endif 