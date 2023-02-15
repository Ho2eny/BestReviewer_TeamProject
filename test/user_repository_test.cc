#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "../src/interface/dto/user/login_request.h"
#include "../src/interface/dto/user/login_response.h"
#include "../src/http/repository/user_http_repository.h"

#include "../src/common/exception/user/fail_login_exception.h"
#include "../src/common/exception/user/fail_logout_exception.h"
#include "../src/common/exception/user/fail_signup_exception.h"
#include "../src/common/exception/user/fail_parse_session_id_exception.h"
#include "../src/http/http_plugin.h"

class MockHttpClient : public HttpPlugin
{
public:
  MOCK_METHOD(Response, Get, (Request), (override));
  MOCK_METHOD(Response, Post, (Request), (override));
  MOCK_METHOD(Response, Put, (Request), (override));
  MOCK_METHOD(Response, Delete, (Request), (override));
};

class UserHttpRepositoryTestFixture : public ::testing::Test
{
protected:
  virtual void SetUp() override
  {
    user_repository_ = std::make_shared<UserHttpRepository>("");
    http_client_ = std::make_shared<MockHttpClient>();
    user_repository_->SetHttpClient(http_client_);
  }

  virtual void TearDown() override
  {
    user_repository_.reset();
  }

  std::shared_ptr<MockHttpClient> http_client_;
  std::shared_ptr<UserHttpRepository> user_repository_;
};

TEST_F(UserHttpRepositoryTestFixture, loginSuccess)
{
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";
  const std::string kValidResponseBody = "{\"session_id\":\"" + kTestSessionId + "\"}";
  Response kValidResponse(200, "", kValidResponseBody);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  LoginRequest temp_request;
  LoginResponse response = user_repository_->Login(temp_request);

  EXPECT_TRUE(response.GetSessionId() == kTestSessionId);
}

TEST_F(UserHttpRepositoryTestFixture, loginSuccessFailedToParseSessionId)
{
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";
  const std::string kInvalidJsonBodyFromServer = "{\"session_id\"" + kTestSessionId + "\"}";

  Response kValidResponse(200, "", kInvalidJsonBodyFromServer);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  LoginRequest temp_request;
  EXPECT_THROW(user_repository_->Login(temp_request), FailParseSessionIdException);
}

TEST_F(UserHttpRepositoryTestFixture, loginFail)
{
  const std::string kErrorMessage = "Account information absence";
  Response kInvalidResponse(400, "", kErrorMessage);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  LoginRequest temp_request;
  EXPECT_THROW(user_repository_->Login(temp_request), FailLoginException);
}

TEST_F(UserHttpRepositoryTestFixture, logoutSuccess)
{
  Response kValidResponse(200, "", "");

  EXPECT_CALL(*http_client_, Delete(testing::_)).WillOnce(testing::Return(kValidResponse));

  LogoutRequest temp_request;
  LogoutResponse response = user_repository_->Logout(temp_request);
}

TEST_F(UserHttpRepositoryTestFixture, logoutFail)
{
  const std::string kErrorMessage = "Invalid Session Id";
  Response kFobiddenResponse(403, "", kErrorMessage);

  EXPECT_CALL(*http_client_, Delete(testing::_)).WillOnce(testing::Return(kFobiddenResponse));

  LogoutRequest temp_request;
  EXPECT_THROW(user_repository_->Logout(temp_request), FailLogoutException);
}

TEST_F(UserHttpRepositoryTestFixture, signupSuccess)
{
  Response kValidResponse(200, "", "");

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  SignupRequest temp_request;
  SignupResponse response = user_repository_->Signup(temp_request);
}

TEST_F(UserHttpRepositoryTestFixture, signupFail)
{
  const std::string kErrorMessage = "Account information absence";
  Response kInvalidResposne(400, "", kErrorMessage);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kInvalidResposne));

  SignupRequest temp_request;
  EXPECT_THROW(user_repository_->Signup(temp_request), FailSignupException);
}

// TODO(in.heo): Prohibited Character 조건 테스트 추가 필요:
// id: [",", "|"], password[","]#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "../src/interface/dto/user/login_request.h"
#include "../src/interface/dto/user/login_response.h"
#include "../src/http/repository/user_http_repository.h"

#include "../src/common/exception/user/fail_login_exception.h"
#include "../src/common/exception/user/fail_logout_exception.h"
#include "../src/common/exception/user/fail_signup_exception.h"
#include "../src/common/exception/user/fail_parse_session_id_exception.h"
#include "../src/http/http_plugin.h"

class MockHttpClient : public HttpPlugin
{
public:
  MOCK_METHOD(Response, Get, (Request), (override));
  MOCK_METHOD(Response, Post, (Request), (override));
  MOCK_METHOD(Response, Put, (Request), (override));
  MOCK_METHOD(Response, Delete, (Request), (override));
};

class UserHttpRepositoryTestFixture : public ::testing::Test
{
protected:
  virtual void SetUp() override
  {
    user_repository_ = std::make_shared<UserHttpRepository>("");
    http_client_ = std::make_shared<MockHttpClient>();
    user_repository_->SetHttpClient(http_client_);
  }

  virtual void TearDown() override
  {
    user_repository_.reset();
  }

  std::shared_ptr<MockHttpClient> http_client_;
  std::shared_ptr<UserHttpRepository> user_repository_;
};

TEST_F(UserHttpRepositoryTestFixture, loginSuccess)
{
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";
  const std::string kValidResponseBody = "{\"session_id\":\"" + kTestSessionId + "\"}";
  Response kValidResponse(200, "", kValidResponseBody);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  LoginRequest temp_request;
  LoginResponse response = user_repository_->Login(temp_request);

  EXPECT_TRUE(response.GetSessionId() == kTestSessionId);
}

TEST_F(UserHttpRepositoryTestFixture, loginSuccessFailedToParseSessionId)
{
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";
  const std::string kInvalidJsonBodyFromServer = "{\"session_id\"" + kTestSessionId + "\"}";

  Response kValidResponse(200, "", kInvalidJsonBodyFromServer);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  LoginRequest temp_request;
  EXPECT_THROW(user_repository_->Login(temp_request), FailParseSessionIdException);
}

TEST_F(UserHttpRepositoryTestFixture, loginFail)
{
  const std::string kErrorMessage = "Account information absence";
  Response kInvalidResponse(400, "", kErrorMessage);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  LoginRequest temp_request;
  EXPECT_THROW(user_repository_->Login(temp_request), FailLoginException);
}

TEST_F(UserHttpRepositoryTestFixture, logoutSuccess)
{
  Response kValidResponse(200, "", "");

  EXPECT_CALL(*http_client_, Delete(testing::_)).WillOnce(testing::Return(kValidResponse));

  LogoutRequest temp_request;
  LogoutResponse response = user_repository_->Logout(temp_request);
}

TEST_F(UserHttpRepositoryTestFixture, logoutFail)
{
  const std::string kErrorMessage = "Invalid Session Id";
  Response kFobiddenResponse(403, "", kErrorMessage);

  EXPECT_CALL(*http_client_, Delete(testing::_)).WillOnce(testing::Return(kFobiddenResponse));

  LogoutRequest temp_request;
  EXPECT_THROW(user_repository_->Logout(temp_request), FailLogoutException);
}

TEST_F(UserHttpRepositoryTestFixture, signupSuccess)
{
  Response kValidResponse(200, "", "");

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  SignupRequest temp_request;
  SignupResponse response = user_repository_->Signup(temp_request);
}

TEST_F(UserHttpRepositoryTestFixture, signupFail)
{
  const std::string kErrorMessage = "Account information absence";
  Response kInvalidResposne(400, "", kErrorMessage);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kInvalidResposne));

  SignupRequest temp_request;
  EXPECT_THROW(user_repository_->Signup(temp_request), FailSignupException);
}

// TODO(in.heo): Prohibited Character 조건 테스트 추가 필요:
// id: [",", "|"], password[","]
