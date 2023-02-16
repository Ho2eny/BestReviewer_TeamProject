#ifndef DNS_RESOLVING_FAILURE_H_
#define DNS_RESOLVING_FAILURE_H_

#include "base_network_exception.h"

class DnsResolvingFailureException : public BaseNetworkException {
public:
  DnsResolvingFailureException(const char* message) : BaseNetworkException(message) {}
};

#endif 