#ifndef LOGIN_RESPONSE_H_
#define LOGIN_RESPONSE_H_

#include <string>

#include "../../../common/exception/base_exception.h"

#include "../base_response.h"

class LoginResponse : public BaseResponse {
public:
  LoginResponse(std::string session_id) : session_id_(session_id) {}

  virtual void ParseJson(const std::string& json) override;

private:
  std::string session_id_;
};

inline std::string LoginResponse::GetSessionId() const {
  return session_id_;
}

#endif
