#ifndef JOIN_RECEIVER_H_
#define JOIN_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "room_receiver.h"
// #include "../../common/exception/user/fail_receive_exception.h"

class JoinReceiver : public RoomReceiver
{
public:
  // JoinReceiver(Cache &cache, std::shared_ptr<RoomRepository> repository) : RoomReceiver(cache, repository) {}

  void Action() override
  {
    // JoinRequest request(sessionID, roomName);
    // Waiting for the implementatino from in.heo
    // JoinRoomResponse response = repository.JoinRoom(request);
  }
};
#endif
