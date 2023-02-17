#ifndef REPOSITORY_TEXT_FIXTURE_H_
#define REPOSITORY_TEXT_FIXTURE_H_

#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "../../src/http/repository/chat_http_repository.h"
#include "../../src/http/repository/room_http_repository.h"
#include "../../src/http/repository/user_http_repository.h"
#include "../../src/http/http_plugin.h"

class MockHttpClient : public HttpPlugin {
public:
  MOCK_METHOD(Response, Get, (Request), (override));
  MOCK_METHOD(Response, Post, (Request), (override));
  MOCK_METHOD(Response, Put, (Request), (override));
  MOCK_METHOD(Response, Delete, (Request), (override));
};

class RepositoryTestFixture : public ::testing::Test {
protected:
  virtual void SetUp() override {
    http_client_ = std::make_shared<MockHttpClient>();
    chat_repository_ = std::make_shared<ChatHttpRepository>("");
    room_repository_ = std::make_shared<RoomHttpRepository>("");
    user_repository_ = std::make_shared<UserHttpRepository>("");
    chat_repository_->SetHttpClient(http_client_);
    room_repository_->SetHttpClient(http_client_);
    user_repository_->SetHttpClient(http_client_);
  }

  virtual void TearDown() override {
    chat_repository_.reset();
    room_repository_.reset();
    user_repository_.reset();
  }

  std::shared_ptr<MockHttpClient> http_client_;
  std::shared_ptr<ChatHttpRepository> chat_repository_;
  std::shared_ptr<RoomHttpRepository> room_repository_;
  std::shared_ptr<UserHttpRepository> user_repository_;
};



#endif
