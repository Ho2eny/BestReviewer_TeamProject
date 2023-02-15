#ifndef LOGIN_REQUEST_H_
#define LOGIN_REQUEST_H_

#include <string>

#include "../base_request.h"

class LoginRequest : public BaseRequest {
public:
  LoginRequest(std::string id, std::string nonce, std::string password) : id_(id), nonce_(nonce), password_(password) {}

private:
  std::string id_;
  std::string nonce_;
  std::string password_;
};

#endif