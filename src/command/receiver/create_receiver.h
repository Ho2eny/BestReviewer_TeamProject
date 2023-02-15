#ifndef CREATE_RECEIVER_H_
#define CREATE_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "room_receiver.h"
// #include "../../common/exception/user/fail_receive_exception.h"

class CreateReceiver : public RoomReceiver
{
public:
  // CreateReceiver(Cache &cache, std::shared_ptr<RoomRepository> repository) : RoomReceiver(cache, repository) {}

  void Action() override
  {
    try
    {
      std::string session_id = GetSessionID();
      std::string room_name = GetRoomName();
      // CreateRoomRequest request(session_id, room_name);
      // CreateRoomResponse response = repository_.CreateRoom(request);
    }
    catch (const InvalidCommandException &ex)
    {
      throw InvalidCommandException(ex.what());
    }
  }
};
#endif
