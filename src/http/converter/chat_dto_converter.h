#ifndef CHAT_DTO_CONVERTER_H_
#define CHAT_DTO_CONVERTER_H_

#include "./json_serializer.h"

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
  // TODO(in.heo): Refactor: Endpoint 관리를 어떻게 할지 고민
  static const std::string kReceiveMessageEndpoint;
  static const std::string kSendMessageEndpoint;

  std::string ConvertToJsonString(const SendMessageRequest& send_message_request) const;

  std::shared_ptr<JsonSerializer> json_serializer_;
};

#endif