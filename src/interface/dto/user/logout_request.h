#ifndef LOGOUT_REQUEST_H_
#define LOGOUT_REQUEST_H_

#include <string>

#include "../base_request.h"

class LogoutRequest : public BaseRequest {
public:
  LogoutRequest() {}
  LogoutRequest(std::string session_id) : session_id_(session_id) {}

  std::string GetSessionId() const;

private:
  std::string session_id_;
};

inline std::string LogoutRequest::GetSessionId() const {
  return session_id_;
}

#endif