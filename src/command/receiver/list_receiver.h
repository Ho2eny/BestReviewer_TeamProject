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
  ListReceiver(Cache &cache, std::shared_ptr<RoomRepository> repository) : RoomReceiver(cache, repository) {}

  void Action() override
  {
    try
    {
      std::string session_id = GetSessionID();
      RetrieveRoomRequest request(session_id);
      RetrieveRoomResponse response = repository_->RetrieveRoom(request);
      cache_.SetRooms(response.GetRoomNames());
    }
    catch (const InvalidCommandException &ex)
    {
      throw InvalidCommandException(ex.what());
    }
  }
};
#endif
