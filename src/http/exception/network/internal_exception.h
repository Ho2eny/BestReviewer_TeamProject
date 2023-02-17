#ifndef INTERNAL_EXCEPTION_H_
#define INTERNAL_EXCEPTION_H_

#include "base_network_exception.h"

class InternalException : public BaseNetworkException {
public:
  InternalException(const char* message) : BaseNetworkException(message) {}
};

#endif 