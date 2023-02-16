#include <gtest/gtest.h>

#include "repository_test_fixture.h"

#include "../../src/common/exception/room/fail_create_room_exception.h"
#include "../../src/common/exception/room/fail_parse_retrieve_room_response_exception.h"
#include "../../src/common/exception/room/fail_retrieve_room_exception.h"
#include "../../src/common/exception/room/invalid_room_repository_exception.h"
#include "../../src/http/exception/network/base_network_exception.h"

TEST_F(RepositoryTestFixture, createRoomSuccess) {
  const std::string kTestRoomName = "Room_Test";
  const std::string kTestSessionId = "MkUdmbzNVZE678CgRV16lL1z5lyGTjal";

  const std::string kValidResponseBody = "{\"chat_room\":\"" + kTestRoomName + "\", \"session_id\":\"" + kTestSessionId + "\"}";
  Response kValidResponse(200, kValidResponseBody);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  CreateRoomRequest temp_request;
  CreateRoomResponse response = room_repository_->CreateRoom(temp_request);
}

TEST_F(RepositoryTestFixture, createRoomFail) {
  const std::string kErrorMessage = "Not a valid session ID";
  Response kForbiddenResponse(403, kErrorMessage);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kForbiddenResponse));

  CreateRoomRequest temp_request;
  EXPECT_THROW(room_repository_->CreateRoom(temp_request), FailCreateRoomException);
}

TEST_F(RepositoryTestFixture, createRoomFailNetworkIssue) {
  auto kNetworkException = BaseNetworkException("DNS resolving failed.");

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Throw(kNetworkException));

  CreateRoomRequest temp_request;
  EXPECT_THROW(room_repository_->CreateRoom(temp_request), FailCreateRoomException);
}

TEST_F(RepositoryTestFixture, retrieveRoomSuccess) {
  const std::string kValidResponseBody = "[{\"room\":\"room_name_1\"},{\"room\":\"room_name_2\"},{\"room\":\"room_name_3\"}]";
  Response kValidResponse(200, kValidResponseBody);
  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Return(kValidResponse));

  RetrieveRoomRequest temp_request;
  RetrieveRoomResponse response = room_repository_->RetrieveRoom(temp_request);

  std::vector<std::string> rooms = response.GetRoomNames();
  EXPECT_TRUE(rooms[0] == "room_name_1");
  EXPECT_TRUE(rooms[1] == "room_name_2");
  EXPECT_TRUE(rooms[2] == "room_name_3");
}

TEST_F(RepositoryTestFixture, retrieveRoomSuccessFailedToParseResponse) {
  const std::string kInvalidJsonResponse = "[{\"room\":\"room_name_1},\"room\":\"room_name_2\",\"room\":\"room_name_3\"}]";
  Response kInvalidResponse(200, kInvalidJsonResponse);

  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  RetrieveRoomRequest temp_request;
  EXPECT_THROW(room_repository_->RetrieveRoom(temp_request), FailParseRetrieveRoomResponseException);
}

TEST_F(RepositoryTestFixture, retrieveRoomFail) {
  const std::string kErrorMessage = "Account information absence";
  Response kInvalidResponse(400, kErrorMessage);

  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  RetrieveRoomRequest temp_request;
  EXPECT_THROW(room_repository_->RetrieveRoom(temp_request), FailRetrieveRoomException);
}

TEST_F(RepositoryTestFixture, retrieveRoomFailNetworkIssue) {
  auto kNetworkException = BaseNetworkException("DNS resolving failed.");

  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Throw(kNetworkException));

  RetrieveRoomRequest temp_request;
  EXPECT_THROW(room_repository_->RetrieveRoom(temp_request), FailRetrieveRoomException);
}

TEST_F(RepositoryTestFixture, exceptionWhenRoomRepositoryIsInvalid) {
  room_repository_->SetHttpClient(nullptr);

  RetrieveRoomRequest temp_request;
  EXPECT_THROW(room_repository_->RetrieveRoom(temp_request), InvalidRoomRepositoryException);
}
