#include "user_http_repository.h"

#include "../../common/exception/user/fail_login_exception.h"
#include "../../common/exception/user/fail_logout_exception.h"
#include "../../common/exception/user/fail_parse_session_id_exception.h"
#include "../../common/exception/user/fail_signup_exception.h"
#include "../thirdparty/curl/curl_client.h"

UserHttpRepository::UserHttpRepository(std::string base_url) : base_url_(base_url) {
  Initialize();
}

LoginResponse UserHttpRepository::Login(const LoginRequest& request) {
  Request http_request = user_dto_converter_->ConvertToLoginHttpRequestFrom(request, base_url_);
  Response http_response = http_client_->Post(http_request);

  if (http_response.GetStatusCode() >= 200 && http_response.GetStatusCode() < 300) {
    LoginResponse login_response;
    try {
      login_response = user_dto_converter_->ConvertToLoginResponseFrom(http_response);
    }
    catch (const BaseException& e) {
      throw FailParseSessionIdException(e.what());
    }

    return login_response;
  }

  throw FailLoginException(http_response.GetErrorMessage().c_str());
}

LogoutResponse UserHttpRepository::Logout(const LogoutRequest& request) {
  Request http_request = user_dto_converter_->ConvertToLogoutHttpRequestFrom(request, base_url_);
  Response http_response = http_client_->Delete(http_request);

  if (http_response.GetStatusCode() >= 200 && http_response.GetStatusCode() < 300)
    return LogoutResponse();

  throw FailLogoutException(http_response.GetErrorMessage().c_str());
}

SignupResponse UserHttpRepository::Signup(const SignupRequest& request) {
  Request http_request = user_dto_converter_->ConvertToSignupHttpRequestFrom(request, base_url_);
  Response http_response = http_client_->Post(http_request);

  if (http_response.GetStatusCode() >= 200 && http_response.GetStatusCode() < 300) {
    return SignupResponse();
  }

  throw FailSignupException(http_response.GetErrorMessage().c_str());
}

void UserHttpRepository::SetHttpClient(const std::shared_ptr<HttpPlugin>& client) {
  http_client_.reset();
  http_client_ = client;
}

void UserHttpRepository::Initialize() {
  CurlClient* curl_client = new CurlClient();
  http_client_ = std::shared_ptr<HttpPlugin>(curl_client);
  user_dto_converter_ = std::make_shared<UserDtoConverter>();
}

