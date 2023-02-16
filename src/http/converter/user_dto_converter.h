#ifndef USER_DTO_CONVERTER_H_
#define USER_DTO_CONVERTER_H_

#include "json_serializer.h"

#include "../../interface/dto/user/login_response.h"
#include "../../interface/dto/user/login_request.h"
#include "../../interface/dto/user/logout_request.h"
#include "../../interface/dto/user/logout_response.h"
#include "../../interface/dto/user/signup_request.h"
#include "../../interface/dto/user/signup_response.h"
#include "../dto/response.h"
#include "../dto/request.h"

class UserDtoConverter {
public:
  UserDtoConverter();

  LoginResponse ConvertToLoginResponseFrom(const Response& http_response) const;
  Request ConvertToLoginHttpRequestFrom(const LoginRequest& login_request, const std::string& base_url) const;

  Request ConvertToLogoutHttpRequestFrom(const LogoutRequest& logout_request, const std::string& base_url) const;

  Request ConvertToSignupHttpRequestFrom(const SignupRequest& signup_request, const std::string& base_url) const;

private:
  // TODO(in.heo): Refactor: Endpoint 관리를 어떻게 할지 고민
  static const std::string kLoginEndpoint;
  static const std::string kLogoutEndpoint;
  static const std::string kSignupEndpoint;

  std::string ConvertToJsonString(const LoginRequest& login_request) const;
  std::string ConvertToJsonString(const SignupRequest& signup_request) const;

  std::shared_ptr<JsonSerializer> json_serializer_;
};

#endif