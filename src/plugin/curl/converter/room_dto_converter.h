#ifndef ROOM_DTO_CONVERTER_H_
#define ROOM_DTO_CONVERTER_H_

#include "../json_serializer.h"

#include "../../../interface/dto/room/create_room_response.h"
#include "../../../interface/dto/room/create_room_request.h"
#include "../../../interface/dto/room/retrieve_room_request.h"
#include "../../../interface/dto/room/retrieve_room_response.h"

#include "../../../response.h"
#include "../../../request.h"

class RoomDtoConverter {
public:
  RoomDtoConverter();

  Request ConvertToCreateRoomHttpRequestFrom(const CreateRoomRequest& create_room_request, const std::string& base_url) const;

  Request ConvertToRetrieveRoomHttpRequestFrom(const RetrieveRoomRequest& retrieve_room_request, const std::string& base_url) const;
  RetrieveRoomResponse ConvertToRetrieveRoomResponseFrom(const Response& http_response) const;

private:
  // TODO(in.heo): Refactor: Endpoint 관리를 어떻게 할지 고민
  static const std::string kCreateRoomEndpoint;
  static const std::string kRetrieveRoomEndpoint;

  std::string ConvertToJsonString(const CreateRoomRequest& create_room_request) const;

  std::shared_ptr<JsonSerializer> json_serializer_;
};

#endif