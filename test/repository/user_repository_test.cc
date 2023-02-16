#include <gtest/gtest.h>

#include "repository_test_fixture.h"

#include "../../src/common/exception/user/fail_login_exception.h"
#include "../../src/common/exception/user/fail_logout_exception.h"
#include "../../src/common/exception/user/fail_signup_exception.h"
#include "../../src/common/exception/user/fail_parse_session_id_exception.h"
#include "../../src/common/exception/user/invalid_user_repository_exception.h"
#include "../../src/http/exception/network/base_network_exception.h"

TEST_F(RepositoryTestFixture, loginSuccess) {
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";
  const std::string kValidResponseBody = "{\"session_id\":\"" + kTestSessionId + "\"}";
  Response kValidResponse(200, kValidResponseBody);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  LoginRequest temp_request;
  LoginResponse response = user_repository_->Login(temp_request);

  EXPECT_TRUE(response.GetSessionId() == kTestSessionId);
}

TEST_F(RepositoryTestFixture, loginSuccessFailedToParseSessionId) {
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";
  const std::string kInvalidJsonBodyFromServer = "{\"session_id\"" + kTestSessionId + "\"}";

  Response kInvalidResponse(200, kInvalidJsonBodyFromServer);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  LoginRequest temp_request;
  EXPECT_THROW(user_repository_->Login(temp_request), FailParseSessionIdException);
}

TEST_F(RepositoryTestFixture, loginFail) {
  const std::string kErrorMessage = "Account information absence";
  Response kInvalidResponse(400, kErrorMessage);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  LoginRequest temp_request;
  EXPECT_THROW(user_repository_->Login(temp_request), FailLoginException);
}

TEST_F(RepositoryTestFixture, loginFailNetworkIssue) {
  auto kNetworkException = BaseNetworkException("DNS resolving failed.");

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Throw(kNetworkException));

  LoginRequest temp_request;
  EXPECT_THROW(user_repository_->Login(temp_request), FailLoginException);
}

TEST_F(RepositoryTestFixture, logoutSuccess) {
  Response kValidResponse(200, "");

  EXPECT_CALL(*http_client_, Delete(testing::_)).WillOnce(testing::Return(kValidResponse));

  LogoutRequest temp_request;
  LogoutResponse response = user_repository_->Logout(temp_request);
}

TEST_F(RepositoryTestFixture, logoutFail) {
  const std::string kErrorMessage = "Invalid Session Id";
  Response kFobiddenResponse(403, kErrorMessage);

  EXPECT_CALL(*http_client_, Delete(testing::_)).WillOnce(testing::Return(kFobiddenResponse));

  LogoutRequest temp_request;
  EXPECT_THROW(user_repository_->Logout(temp_request), FailLogoutException);
}

TEST_F(RepositoryTestFixture, logoutFailNetworkIssue) {
  auto kNetworkException = BaseNetworkException("DNS resolving failed.");

  EXPECT_CALL(*http_client_, Delete(testing::_)).WillOnce(testing::Throw(kNetworkException));

  LogoutRequest temp_request;
  EXPECT_THROW(user_repository_->Logout(temp_request), FailLogoutException);
}

TEST_F(RepositoryTestFixture, signupSuccess) {
  Response kValidResponse(200, "");

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  SignupRequest temp_request;
  SignupResponse response = user_repository_->Signup(temp_request);
}

TEST_F(RepositoryTestFixture, signupFail) {
  const std::string kErrorMessage = "Account information absence";
  Response kInvalidResposne(400, kErrorMessage);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kInvalidResposne));

  SignupRequest temp_request;
  EXPECT_THROW(user_repository_->Signup(temp_request), FailSignupException);
}

TEST_F(RepositoryTestFixture, signupFailNetworkIssue) {
  auto kNetworkException = BaseNetworkException("DNS resolving failed.");

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Throw(kNetworkException));

  SignupRequest temp_request;
  EXPECT_THROW(user_repository_->Signup(temp_request), FailSignupException);
}

TEST_F(RepositoryTestFixture, exceptionWhenUserRepositoryIsInvalid) {
  user_repository_->SetHttpClient(nullptr);

  SignupRequest temp_request;
  EXPECT_THROW(user_repository_->Signup(temp_request), InvalidUserRepositoryException);
}

// TODO(in.heo): Prohibited Character 조건 테스트 추가 필요:
// id: [",", "|"], password[","]