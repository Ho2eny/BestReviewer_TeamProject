#ifndef LOGIN_RESPONSE_H_
#define LOGIN_RESPONSE_H_

#include <string>

#include "../../../common/exception/base_exception.h"

#include "../base_response.h"
#include "../json_serializable.h"
#include "../../json_serializer.h"

class LoginResponse : public BaseResponse, public JsonSerializable {
public:
  LoginResponse(std::string session_id) : session_id_(session_id) {}

  virtual void ParseJson(const std::string& json) override;

  virtual std::string ToJson() override;

  std::string GetSessionId() const;

private:
  std::string session_id_;
};

inline void LoginResponse::ParseJson(const std::string& json) {
  Json::Value json_object;
  try {
    json_object = JsonSerializer::ParseJson(json);
  }
  catch (const BaseException& e) {
    std::cerr << "Failed to parse LoginResponse: " << e.what() << std::endl;
  }

  session_id_ = json_object["session_id"];
}

inline std::string LoginResponse::ToJson() {
  // TODO(in.heo): Not high priority
  return "";
}

inline std::string LoginResponse::GetSessionId() const {
  return session_id_;
}

#endif
