#ifndef BASE_NETWORK_EXCEPTION_H_
#define BASE_NETWORK_EXCEPTION_H_

#include <exception>

class BaseNetworkException : public std::exception {
public:
  BaseNetworkException(const char* message) : message_(message) {}

  virtual const char* what() const noexcept override
  {
    return message_.c_str();
  }

private:
  std::string message_;
};

#endif 