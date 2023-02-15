#ifndef LIST_RECEIVER_H_
#define LIST_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "room_receiver.h"
// #include "../../common/exception/user/fail_receive_exception.h"

class ListReceiver : public RoomReceiver
{
public:
  // ListReceiver(Cache &cache, std::shared_ptr<RoomRepository> repository) : RoomReceiver(cache, repository) {}

  void Action() override
  {
    try
    {
      std::string session_id = GetSessionID();
      // ListRequest request(sessionID);
      // Waiting for the implementatino from in.heo
      // GetRoomList response = repository.getRoomList(request);
    }
    catch (const InvalidCommandException &ex)
    {
      throw InvalidCommandException(ex.what());
    }
  }
};
#endif
