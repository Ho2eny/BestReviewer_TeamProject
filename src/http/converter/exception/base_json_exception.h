#ifndef BASE_JSON_EXCEPTION_H_
#define BASE_JSON_EXCEPTION_H_

#include <exception>

class BaseJsonException : public std::exception {
public:
  BaseJsonException(const char* message) : message_(message) {}

  virtual const char* what() const noexcept override
  {
    return message_.c_str();
  }

private:
  std::string message_;
};

#endif 