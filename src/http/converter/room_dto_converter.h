#ifndef ROOM_DTO_CONVERTER_H_
#define ROOM_DTO_CONVERTER_H_

#include "json_serializer.h"

#include "../../interface/dto/room/create_room_response.h"
#include "../../interface/dto/room/create_room_request.h"
#include "../../interface/dto/room/retrieve_room_request.h"
#include "../../interface/dto/room/retrieve_room_response.h"

#include "../dto/response.h"
#include "../dto/request.h"

class RoomDtoConverter {
public:
  RoomDtoConverter();

  Request ConvertToCreateRoomHttpRequestFrom(const CreateRoomRequest& create_room_request, const std::string& base_url) const;

  Request ConvertToRetrieveRoomHttpRequestFrom(const RetrieveRoomRequest& retrieve_room_request, const std::string& base_url) const;
  RetrieveRoomResponse ConvertToRetrieveRoomResponseFrom(const Response& http_response) const;

private:
  static const std::string kCreateRoomEndpoint;
  static const std::string kRetrieveRoomEndpoint;
  static const std::string kSessionIdKey;

  std::string ConvertToJsonString(const CreateRoomRequest& create_room_request) const;

  std::string GetRetrieveRoomEndpoint(const RetrieveRoomRequest& retrieve_room_request) const;

  std::shared_ptr<JsonSerializer> json_serializer_;
};

#endif