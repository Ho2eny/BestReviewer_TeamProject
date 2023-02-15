#ifndef USER_CONVERTER_H_
#define USER_CONVERTER_H_

#include "../json_serializer.h"

#include "../../../interface/dto/user/login_response.h"
#include "../../../interface/dto/user/login_request.h"
#include "../../../response.h"
#include "../../../request.h"

class UserDtoConverter {
public:
  UserDtoConverter();

  LoginResponse ConvertToLoginResponseFrom(const Response& http_response) const;
  Request ConvertToLoginHttpRequestFrom(const LoginRequest& login_request, const std::string& base_url) const;

private:
  static const std::string kLoginEndpoint;

  std::string ConvertToJsonString(const LoginRequest& login_request) const;

  std::shared_ptr<JsonSerializer> json_serializer_;
};


#endif
