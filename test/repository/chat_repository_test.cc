#include <gtest/gtest.h>

#include "repository_test_fixture.h"

#include "../../src/common/exception/chat/fail_parse_receive_message_reseponse_exception.h"
#include "../../src/common/exception/chat/fail_receive_message_exception.h"
#include "../../src/common/exception/chat/fail_send_message_exception.h"
#include "../../src/common/exception/chat/invalid_chat_repository_exception.h"
#include "../../src/http/exception/network/base_network_exception.h"

TEST_F(RepositoryTestFixture, sendMessageSuccess) {
  Response kValidResponse(200, "");

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kValidResponse));

  SendMessageRequest temp_request;
  SendMessageResponse response = chat_repository_->SendMessage(temp_request);
}

TEST_F(RepositoryTestFixture, sendMessageFail) {
  const std::string error_message = "Can't find user ID from given session ID";
  Response kServerInternalErrorResponse(403, error_message);

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Return(kServerInternalErrorResponse));

  SendMessageRequest temp_request;
  EXPECT_THROW(chat_repository_->SendMessage(temp_request), FailSendMessageException);
}

TEST_F(RepositoryTestFixture, sendMessageFailNetworkIssue) {
  auto kNetworkException = BaseNetworkException("DNS resolving failed.");

  EXPECT_CALL(*http_client_, Post(testing::_)).WillOnce(testing::Throw(kNetworkException));

  SendMessageRequest temp_request;
  EXPECT_THROW(chat_repository_->SendMessage(temp_request), FailSendMessageException);
}

TEST_F(RepositoryTestFixture, receiveMessageSuccess) {
  const std::string kValidResponseBody = "[{\"date\":1583135236,\"message\":\"hello\",\"room\":\"2\",\"user_id\":\"samsung\"},{\"date\":1602568577,\"message\":\"test\",\"room\":\"2\",\"user_id\":\"test\"}]";

  Response kValidResponse(200, kValidResponseBody);

  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Return(kValidResponse));

  ReceiveMessageRequest temp_request;
  ReceiveMessageResponse response = chat_repository_->ReceiveMessage(temp_request);

  std::vector<Message> messages = response.GetMessages();
  EXPECT_TRUE(messages[0].GetDate() == 1583135236 && messages[1].GetDate() == 1602568577);
  EXPECT_TRUE(messages[0].GetMessage() == "hello" && messages[1].GetMessage() == "test");
  EXPECT_TRUE(messages[0].GetRoomName() == "2" && messages[1].GetRoomName() == "2");
  EXPECT_TRUE(messages[0].GetUserId() == "samsung" && messages[1].GetUserId() == "test");
}

TEST_F(RepositoryTestFixture, receiveMessageSuccessFailedToParseResponse) {
  const std::string kInvalidJsonResponse = "[{\"date\":1583135236,\"message:\"hello,\"room\":\"2\",\"user_id\":\"samsung\",{\"date\":1602568577,\"message\":\"test\",\"room\":\"2\",\"user_id\":\"test\"}]";

  Response kInvalidResponse(200, kInvalidJsonResponse);

  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Return(kInvalidResponse));

  ReceiveMessageRequest temp_request;
  EXPECT_THROW(chat_repository_->ReceiveMessage(temp_request), FailParseReceiveMessageResponseException);
}

TEST_F(RepositoryTestFixture, receiveMessageFail) {
  const std::string kErrorMessage = "Not a valid session ID";
  Response kForbiddenResponse(403, kErrorMessage);

  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Return(kForbiddenResponse));

  ReceiveMessageRequest temp_request;
  EXPECT_THROW(chat_repository_->ReceiveMessage(temp_request), FailReceiveMessageException);
}

TEST_F(RepositoryTestFixture, receiveMessageFailNetworkIssue) {
  auto kNetworkException = BaseNetworkException("DNS resolving failed.");

  EXPECT_CALL(*http_client_, Get(testing::_)).WillOnce(testing::Throw(kNetworkException));

  ReceiveMessageRequest temp_request;
  EXPECT_THROW(chat_repository_->ReceiveMessage(temp_request), FailReceiveMessageException);
}

TEST_F(RepositoryTestFixture, exceptionWhenChatRepositoryIsInvalid) {
  chat_repository_->SetHttpClient(nullptr);

  ReceiveMessageRequest temp_request;
  EXPECT_THROW(chat_repository_->ReceiveMessage(temp_request), InvalidChatRepositoryException);
}
