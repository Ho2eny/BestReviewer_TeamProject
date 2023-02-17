#include "chat_dto_converter.h"

const std::string ChatDtoConverter::kSendMessageEndpoint = "/chat/chatmessage";
const std::string ChatDtoConverter::kReceiveMessageEndpoint = "/chat/chatmessage?session_id=:session_id&chat_room=:chat_room";
const std::string ChatDtoConverter::kSessionIdKey = ":session_id";
const std::string ChatDtoConverter::kChatRoomKey = ":chat_room";

ChatDtoConverter::ChatDtoConverter() {
  json_serializer_ = std::make_shared<JsonSerializer>();
}

Request ChatDtoConverter::ConvertToReceiveMessageHttpRequestFrom(
    const ReceiveMessageRequest& receive_message_request, const std::string& base_url) const {
  Request http_request(base_url);

  std::string path = GetReceiveMessageEndpoint(receive_message_request);
  http_request.SetPath(path);

  return http_request;
}

ReceiveMessageResponse ChatDtoConverter::ConvertToReceiveMessageResponseFrom(const Response& http_response) const {
  Json::Value json_object;

  json_object = json_serializer_->ParseJson(http_response.GetBody());

  std::vector<Message> messages;
  for (Json::ArrayIndex i = 0; i < json_object.size(); ++i) {
    messages.emplace_back(json_object[i]["date"].asInt(),
      json_object[i]["message"].asString(),
      json_object[i]["room"].asString(),
      json_object[i]["user_id"].asString());
  }

  return ReceiveMessageResponse(messages);
}

Request ChatDtoConverter::ConvertToSendMessageHttpRequestFrom(const SendMessageRequest& send_message_request, const std::string& base_url) const {
  Request http_request(base_url);
  http_request.SetPath(kSendMessageEndpoint);
  http_request.SetBody(ConvertToJsonString(send_message_request));

  return http_request;
}

std::string ChatDtoConverter::ConvertToJsonString(const SendMessageRequest& send_message_request) const {
  Json::Value json_object;
  json_object["chat_message"] = send_message_request.GetMessage();
  json_object["chat_room"] = send_message_request.GetRoomName();
  json_object["session_id"] = send_message_request.GetSessionId();

  return json_serializer_->ToString(json_object);
}

std::string ChatDtoConverter::GetReceiveMessageEndpoint(const ReceiveMessageRequest& receive_message_request) const {
  std::string receive_message_endpoint = kReceiveMessageEndpoint;

  auto pos = receive_message_endpoint.find(kSessionIdKey);
  receive_message_endpoint.replace(pos, kSessionIdKey.length(), receive_message_request.GetSessionId());

  pos = receive_message_endpoint.find(kChatRoomKey);
  receive_message_endpoint.replace(pos, kChatRoomKey.length(), receive_message_request.GetRoomName());

  return receive_message_endpoint;
}
