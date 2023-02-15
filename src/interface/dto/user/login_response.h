#ifndef LOGIN_RESPONSE_H_
#define LOGIN_RESPONSE_H_

#include <string>

#include "../../../common/exception/base_exception.h"

#include "../base_response.h"

class LoginResponse : public BaseResponse {
public:
  LoginResponse() {}
  LoginResponse(std::string session_id) : session_id_(session_id) {}

  std::string GetSessionId() const;

private:
  std::string session_id_;
};

inline std::string LoginResponse::GetSessionId() const {
  return session_id_;
}

#endif
