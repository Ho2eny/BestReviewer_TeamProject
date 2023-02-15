#ifndef USER_CONVERTER_H_
#define USER_CONVERTER_H_

#include "../json_serializer.h"

#include "../../../interface/dto/user/login_response.h"
#include "../../../interface/dto/user/login_request.h"
#include "../../../response.h"

class UserDtoConverter {
public:
  UserDtoConverter();

  LoginResponse ConvertToLoginResponseFrom(const Response& http_response) const;

private:
  std::shared_ptr<JsonSerializer> json_serializer_;
};

inline UserDtoConverter::UserDtoConverter() {
  json_serializer_ = std::make_shared<JsonSerializer>();
}

inline LoginResponse ConvertToLoginResponseFrom(const Response& http_response) const {
  Json::Value json_object;
  try {
    json_object = JsonSerializer::ParseJson(http_response.GetBody());
  }
  catch (const BaseException& e) {
    std::cerr << "Failed to parse LoginResponse: " << e.what() << std::endl;
  }

  // TODO(in.heo): json_object["session_id"]가 없을 경우 Exception 추가
  return LoginResponse(json_object["session_id"]);
}

#endif
