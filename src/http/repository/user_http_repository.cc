#include "user_http_repository.h"

#include "../converter/exception/base_json_exception.h"
#include "../exception/network/base_network_exception.h"
#include "../../common/exception/user/fail_login_exception.h"
#include "../../common/exception/user/fail_logout_exception.h"
#include "../../common/exception/user/fail_parse_session_id_exception.h"
#include "../../common/exception/user/fail_signup_exception.h"
#include "../../common/exception/user/invalid_user_repository_exception.h"
#include "../thirdparty/curl/curl_client.h"

UserHttpRepository::UserHttpRepository(std::string base_url) : base_url_(base_url) {
  Initialize();
}

LoginResponse UserHttpRepository::Login(const LoginRequest& request) {
  if (!CheckPrecondition()) throw InvalidUserRepositoryException("Conveter or HttpClient is not valid");

  Request http_request = user_dto_converter_->ConvertToLoginHttpRequestFrom(request, base_url_);

  try {
    Response http_response = http_client_->Post(http_request);

    if (http_response.IsSuccess()) {
      LoginResponse login_response;
      login_response = user_dto_converter_->ConvertToLoginResponseFrom(http_response);
      return login_response;
    }
    else {
      throw FailLoginException(http_response.GetBody().c_str());
    }
  }
  catch (const BaseNetworkException& e) {
    throw FailLoginException(e.what());
  }
  catch (const BaseJsonException& e) {
    throw FailParseSessionIdException(e.what());
  }
}

LogoutResponse UserHttpRepository::Logout(const LogoutRequest& request) {
  if (!CheckPrecondition()) throw InvalidUserRepositoryException("Conveter or HttpClient is not valid");

  Request http_request = user_dto_converter_->ConvertToLogoutHttpRequestFrom(request, base_url_);

  try {
    Response http_response = http_client_->Delete(http_request);
    if (http_response.IsSuccess()) return LogoutResponse();
    else throw FailLogoutException(http_response.GetBody().c_str());
  }
  catch (const BaseNetworkException& e) {
    throw FailLogoutException(e.what());
  }
}

SignupResponse UserHttpRepository::Signup(const SignupRequest& request) {
  if (!CheckPrecondition()) throw InvalidUserRepositoryException("Conveter or HttpClient is not valid");

  Request http_request = user_dto_converter_->ConvertToSignupHttpRequestFrom(request, base_url_);

  try {
    Response http_response = http_client_->Post(http_request);
    if (http_response.IsSuccess()) return SignupResponse();
    else throw FailSignupException(http_response.GetBody().c_str());
  }
  catch (const BaseNetworkException& e) {
    throw FailSignupException(e.what());
  }
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

bool UserHttpRepository::CheckPrecondition() const {
  return (http_client_ != nullptr && user_dto_converter_ != nullptr);
}
