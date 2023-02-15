#ifndef DNS_RESOLVING_FAILURE_H_
#define DNS_RESOLVING_FAILURE_H_

#include "../base_exception.h"

class DnsResolvingFailureException : public BaseException {
public:
  DnsResolvingFailureException(const char* message) : BaseException(message) {}
};

#endif 