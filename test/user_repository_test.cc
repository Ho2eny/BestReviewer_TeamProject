#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "../src/interface/dto/user/login_request.h"
#include "../src/interface/dto/user/login_response.h"
#include "../src/plugin/curl/repository/user_http_repository.h"

#include "../src/common/exception/user/fail_login_exception.h"
#include "../src/common/exception/user/fail_parse_session_id_exception.h"
#include "../src/http_plugin.h"

class MockHttpClient : public HttpPlugin {
public:
  MOCK_METHOD(Response, Get, (Request), (override));
  MOCK_METHOD(Response, Post, (Request), (override));
  MOCK_METHOD(Response, Put, (Request), (override));
  MOCK_METHOD(Response, Delete, (Request), (override));
};

class UserHttpRepositoryTestFixture : public ::testing::Test {
protected:
  virtual void SetUp() override {
    user_repository_ = std::make_shared<UserHttpRepository>("");
    http_client_ = std::make_shared<MockHttpClient>();
    user_repository_->SetHttpClient(http_client_);
  }

  virtual void TearDown() override {
    user_repository_.reset();
  }

  std::shared_ptr<MockHttpClient> http_client_;
  std::shared_ptr<UserHttpRepository> user_repository_;
};

TEST_F(UserHttpRepositoryTestFixture, loginSuccess) {
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";
  const std::string kValidResponseBody = "{\"session_id\":\"" + kTestSessionId + "\"}";
  Response kValidResponse(200, "", kValidResponseBody);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  LoginRequest temp_request;
  LoginResponse response = user_repository_->Login(temp_request);

  EXPECT_TRUE(response.GetSessionId() == kTestSessionId);
}

TEST_F(UserHttpRepositoryTestFixture, loginSuccessFailedToParseSessionId) {
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";
  const std::string kInvalidJsonBodyFromServer = "{\"session_id\"" + kTestSessionId + "\"}";

  Response kValidResponse(200, "", kInvalidJsonBodyFromServer);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  LoginRequest temp_request;
  EXPECT_THROW(user_repository_->Login(temp_request), FailParseSessionIdException);
}

TEST_F(UserHttpRepositoryTestFixture, loginFail) {
  const std::string kErrorMessage = "Account information absence";
  Response kInvalidResponse(400, kErrorMessage, "");

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  LoginRequest temp_request;
  EXPECT_THROW(user_repository_->Login(temp_request), FailLoginException);
}
