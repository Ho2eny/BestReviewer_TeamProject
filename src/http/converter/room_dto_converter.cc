#include "room_dto_converter.h"

const std::string RoomDtoConverter::kCreateRoomEndpoint = "/chat/chatroom";
const std::string RoomDtoConverter::kRetrieveRoomEndpoint = "/chat/chatroom";

RoomDtoConverter::RoomDtoConverter() {
  json_serializer_ = std::make_shared<JsonSerializer>();
}

Request RoomDtoConverter::ConvertToCreateRoomHttpRequestFrom(const CreateRoomRequest& create_room_request, const std::string& base_url) const {
  Request http_request(base_url);
  http_request.SetPath(kCreateRoomEndpoint);
  http_request.SetBody(ConvertToJsonString(create_room_request));

  return http_request;
}

Request RoomDtoConverter::ConvertToRetrieveRoomHttpRequestFrom(const RetrieveRoomRequest& retrieve_room_request, const std::string& base_url) const {
  Request http_request(base_url);

  std::string path = kRetrieveRoomEndpoint + "?" + "session_id=" + retrieve_room_request.GetSessionId();
  http_request.SetPath(path);

  return http_request;
}

RetrieveRoomResponse RoomDtoConverter::ConvertToRetrieveRoomResponseFrom(const Response& http_response) const {
  Json::Value json_object;

  try {
    json_object = json_serializer_->ParseJson(http_response.GetBody());
  }
  catch (const BaseJsonException& e) {
    throw e;
  }

  std::vector<std::string> room_names;
  for (Json::ArrayIndex i = 0; i < json_object.size(); ++i) {
    room_names.emplace_back(json_object[i]["room"].asString());
  }
  return RetrieveRoomResponse(room_names);
}

std::string RoomDtoConverter::ConvertToJsonString(const CreateRoomRequest& create_room_request) const {
  Json::Value json_object;
  json_object["chat_room"] = create_room_request.GetRoomName();
  json_object["session_id"] = create_room_request.GetSessionId();

  // TODO(in.heo): throw exception when json_serializer_ is nullptr
  return json_serializer_->ToString(json_object);
}
