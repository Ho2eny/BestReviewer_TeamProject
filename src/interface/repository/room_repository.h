#ifndef ROOM_REPOSITORY_H_
#define ROOM_REPOSITORY_H_

#include "../dto/room/create_room_request.h"
#include "../dto/room/create_room_response.h"
#include "../dto/room/retrieve_room_request.h"
#include "../dto/room/retrieve_room_response.h"

class RoomRepository {
public:
  virtual CreateRoomResponse CreateRoom(const CreateRoomRequest& request) = 0;

  virtual RetrieveRoomResponse RetrieveRoom(const RetrieveRoomRequest& request) = 0;
};

#endif
