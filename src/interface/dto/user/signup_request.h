#ifndef SIGNUP_REQUEST_H_
#define SIGNUP_REQUEST_H_

#include <string>

#include "../base_request.h"

class SignupRequest : public BaseRequest {
public:
  SignupRequest() {}
  SignupRequest(std::string id, std::string password) : id_(id), password_(password) {}

  std::string GetId() const;
  std::string GetPassword() const;

private:
  std::string id_;
  std::string password_;
};

inline std::string SignupRequest::GetId() const {
  return id_;
}

inline std::string SignupRequest::GetPassword() const {
  return password_;
}

#endif