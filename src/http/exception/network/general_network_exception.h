#ifndef GENERAL_NETWORK_EXCEPTION_H_
#define GENERAL_NETWORK_EXCEPTION_H_

#include "../../../common/exception/base_exception.h"

class GeneralNetworkException : public BaseException
{
public:
  GeneralNetworkException(const char *message) : BaseException(message) {}
};

#endif
