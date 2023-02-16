#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "../../src/http/repository/room_http_repository.h"

#include "../../src/common/exception/room/fail_create_room_exception.h"
#include "../../src/common/exception/room/fail_parse_retrieve_room_response_exception.h"
#include "../../src/common/exception/room/fail_retrieve_room_exception.h"
#include "../../src/http/http_plugin.h"

class MockHttpClient : public HttpPlugin {
public:
  MOCK_METHOD(Response, Get, (Request), (override));
  MOCK_METHOD(Response, Post, (Request), (override));
  MOCK_METHOD(Response, Put, (Request), (override));
  MOCK_METHOD(Response, Delete, (Request), (override));
};

class RoomHttpRepositoryTestFixture : public ::testing::Test {
protected:
  virtual void SetUp() override {
    room_repository_ = std::make_shared<RoomHttpRepository>("");
    http_client_ = std::make_shared<MockHttpClient>();
    room_repository_->SetHttpClient(http_client_);
  }

  virtual void TearDown() override {
    room_repository_.reset();
  }

  std::shared_ptr<MockHttpClient> http_client_;
  std::shared_ptr<RoomHttpRepository> room_repository_;
};

TEST_F(RoomHttpRepositoryTestFixture, createRoomSuccess) {
  const std::string kTestRoomName = "Room_Test";
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";

  const std::string kValidResponseBody = "{\"chat_room\":\"" + kTestRoomName + "\", \"session_id\":\"" + kTestSessionId + "\"}";
  Response kValidResponse(200, "", kValidResponseBody);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  CreateRoomRequest temp_request;
  CreateRoomResponse response = room_repository_->CreateRoom(temp_request);
}

TEST_F(RoomHttpRepositoryTestFixture, createRoomFail) {
  const std::string kErrorMessage = "Not a valid session ID";
  Response kForbiddenResponse(403, "", kErrorMessage);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kForbiddenResponse));

  CreateRoomRequest temp_request;
  EXPECT_THROW(room_repository_->CreateRoom(temp_request), FailCreateRoomException);
}

TEST_F(RoomHttpRepositoryTestFixture, retrieveRoomSuccess) {
  const std::string kValidResponseBody = "[{\"room\":\"room_name_1\"},{\"room\":\"room_name_2\"},{\"room\":\"room_name_3\"}]";
  Response kValidResponse(200, "", kValidResponseBody);
  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Return(kValidResponse));

  RetrieveRoomRequest temp_request;
  RetrieveRoomResponse response = room_repository_->RetrieveRoom(temp_request);

  std::vector<std::string> rooms = response.GetRoomNames();
  EXPECT_TRUE(rooms[0] == "room_name_1");
  EXPECT_TRUE(rooms[1] == "room_name_2");
  EXPECT_TRUE(rooms[2] == "room_name_3");
}

TEST_F(RoomHttpRepositoryTestFixture, retrieveRoomSuccessFailedToParseResponse) {
  const std::string kInvalidJsonResponse = "[{\"room\":\"room_name_1},\"room\":\"room_name_2\",\"room\":\"room_name_3\"}]";
  Response kInvalidResponse(200, "", kInvalidJsonResponse);

  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  RetrieveRoomRequest temp_request;
  EXPECT_THROW(room_repository_->RetrieveRoom(temp_request), FailParseRetrieveRoomResponseException);
}

TEST_F(RoomHttpRepositoryTestFixture, retrieveRoomFail) {
  const std::string kErrorMessage = "Account information absence";
  Response kInvalidResponse(400, "", kErrorMessage);

  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  RetrieveRoomRequest temp_request;
  EXPECT_THROW(room_repository_->RetrieveRoom(temp_request), FailRetrieveRoomException);
}
