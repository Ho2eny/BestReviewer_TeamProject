#include "user_dto_converter.h"

const std::string UserDtoConverter::kLoginEndpoint = "/chat/login";
const std::string UserDtoConverter::kLogoutEndpoint = "/chat/session";
const std::string UserDtoConverter::kSignupEndpoint = "/chat/account";

UserDtoConverter::UserDtoConverter() {
  json_serializer_ = std::make_shared<JsonSerializer>();
}

LoginResponse UserDtoConverter::ConvertToLoginResponseFrom(const Response& http_response) const {
  Json::Value json_object;
  json_object = json_serializer_->ParseJson(http_response.GetBody());

  // TODO(in.heo): json_object["session_id"]가 없을 경우 Exception 추가
  const std::string session_id = json_object["session_id"].asString();

  return LoginResponse(session_id);
}

Request UserDtoConverter::ConvertToLoginHttpRequestFrom(const LoginRequest& login_request, const std::string& base_url) const {
  Request http_request(base_url);
  http_request.SetPath(kLoginEndpoint);
  http_request.SetBody(ConvertToJsonString(login_request));

  return http_request;
}

Request UserDtoConverter::ConvertToLogoutHttpRequestFrom(const LogoutRequest& logout_request, const std::string& base_url) const {
  Request http_request(base_url);

  std::string path = kLogoutEndpoint + "?" + "session_id=" + logout_request.GetSessionId();
  http_request.SetPath(path);

  return http_request;
}

Request UserDtoConverter::ConvertToSignupHttpRequestFrom(const SignupRequest& signup_request, const std::string& base_url) const {
  Request http_request(base_url);
  http_request.SetPath(kSignupEndpoint);

  http_request.SetBody(ConvertToJsonString(signup_request));

  return http_request;
}

std::string UserDtoConverter::ConvertToJsonString(const LoginRequest& login_request) const {
  Json::Value json_object;
  json_object["id"] = login_request.GetId();
  json_object["nonce"] = login_request.GetNonce();
  json_object["password"] = login_request.GetPassword();

  return json_serializer_->ToString(json_object);
}

std::string UserDtoConverter::ConvertToJsonString(const SignupRequest& signup_request) const {
  Json::Value json_object;
  json_object["id"] = signup_request.GetId();
  json_object["password"] = signup_request.GetPassword();

  return json_serializer_->ToString(json_object);
}
