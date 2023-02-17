#ifndef BASE_EXCEPTION_H_
#define BASE_EXCEPTION_H_

#include <exception>
#include <string>

class BaseException : public std::exception {
public:
  BaseException(const char* message) : message_(message) {}

  virtual const char* what() const noexcept override
  {
    return message_.c_str();
  }

private:
  std::string message_;
};

#endif 