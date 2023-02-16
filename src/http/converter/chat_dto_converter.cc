#include "chat_dto_converter.h"

// TODO(in.heo): Request param을 포함한 endpoint 설정후 replace 하는 식으로 수정
const std::string ChatDtoConverter::kReceiveMessageEndpoint = "/chat/chatmessage";
const std::string ChatDtoConverter::kSendMessageEndpoint = "/chat/chatmessage";

ChatDtoConverter::ChatDtoConverter() {
  json_serializer_ = std::make_shared<JsonSerializer>();
}

Request ChatDtoConverter::ConvertToReceiveMessageHttpRequestFrom(
    const ReceiveMessageRequest& receive_message_request, const std::string& base_url) const {
  Request http_request(base_url);

  std::string path = kReceiveMessageEndpoint + "?" + "session_id=" + receive_message_request.GetSessionId() + "&" + "chat_room=" + receive_message_request.GetRoomName();
  http_request.SetPath(path);

  return http_request;
}

ReceiveMessageResponse ChatDtoConverter::ConvertToReceiveMessageResponseFrom(const Response& http_response) const {
  Json::Value json_object;

  try {
    json_object = json_serializer_->ParseJson(http_response.GetBody());
  }
  catch (const BaseJsonException& e) {
    throw e;
  }

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

  // TODO(in.heo): throw exception when json_serializer_ is nullptr
  return json_serializer_->ToString(json_object);
}
