#ifndef LOGIN_REQUEST_H_
#define LOGIN_REQUEST_H_

#include <string>

#include "../base_request.h"

class LoginRequest : public BaseRequest {
public:
  LoginRequest() {}
  LoginRequest(std::string id, std::string nonce, std::string password) : id_(id), nonce_(nonce), password_(password) {}

  std::string GetId() const;
  std::string GetNonce() const;
  std::string GetPassword() const;

private:
  std::string id_;
  std::string nonce_;
  std::string password_;
};

inline std::string LoginRequest::GetId() const {
  return id_;
}

inline std::string LoginRequest::GetNonce() const {
  return nonce_;
}

inline std::string LoginRequest::GetPassword() const {
  return password_;
}

#endif