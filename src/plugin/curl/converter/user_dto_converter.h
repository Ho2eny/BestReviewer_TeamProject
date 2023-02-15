#ifndef USER_CONVERTER_H_
#define USER_CONVERTER_H_

#include "../json_serializer.h"

#include "../../../interface/dto/user/login_response.h"
#include "../../../interface/dto/user/login_request.h"
#include "../../../interface/dto/user/logout_request.h"
#include "../../../interface/dto/user/logout_response.h"
#include "../../../interface/dto/user/signup_request.h"
#include "../../../interface/dto/user/signup_response.h"

#include "../../../response.h"
#include "../../../request.h"

class UserDtoConverter {
public:
  UserDtoConverter();

  LoginResponse ConvertToLoginResponseFrom(const Response& http_response) const;
  Request ConvertToLoginHttpRequestFrom(const LoginRequest& login_request, const std::string& base_url) const;

  Request ConvertToLogoutHttpRequestFrom(const LogoutRequest& logout_request, const std::string& base_url) const;

  Request ConvertToSignupHttpRequestFrom(const SignupRequest& signup_request, const std::string& base_url) const;

private:
  static const std::string kLoginEndpoint;
  static const std::string kLogoutEndpoint;
  static const std::string kSignupEndpoint;

  std::string ConvertToJsonString(const LoginRequest& login_request) const;
  std::string ConvertToJsonString(const SignupRequest& login_request) const;

  std::shared_ptr<JsonSerializer> json_serializer_;
};


#endif
