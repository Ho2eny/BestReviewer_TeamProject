#ifndef CHAT_DTO_CONVERTER_H_
#define CHAT_DTO_CONVERTER_H_

#include "json_serializer.h"

#include "../../interface/dto/chat/receive_message_request.h"
#include "../../interface/dto/chat/receive_message_response.h"
#include "../../interface/dto/chat/send_message_request.h"
#include "../../interface/dto/chat/send_message_response.h"

#include "../dto/response.h"
#include "../dto/request.h"


class ChatDtoConverter {
public:
  ChatDtoConverter();

  Request ConvertToReceiveMessageHttpRequestFrom(const ReceiveMessageRequest& receive_message_request, const std::string& base_url) const;
  ReceiveMessageResponse ConvertToReceiveMessageResponseFrom(const Response& http_response) const;

  Request ConvertToSendMessageHttpRequestFrom(const SendMessageRequest& send_message_request, const std::string& base_url) const;

private:
  static const std::string kReceiveMessageEndpoint;
  static const std::string kSendMessageEndpoint;
  static const std::string kSessionIdKey;
  static const std::string kChatRoomKey;

  std::string ConvertToJsonString(const SendMessageRequest& send_message_request) const;

  std::string GetReceiveMessageEndpoint(const ReceiveMessageRequest& receive_message_request) const;

  std::shared_ptr<JsonSerializer> json_serializer_;
};

#endif