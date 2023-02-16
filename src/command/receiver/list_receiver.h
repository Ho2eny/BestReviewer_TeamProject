#ifndef LIST_RECEIVER_H_
#define LIST_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "room_receiver.h"

class ListReceiver : public RoomReceiver
{
public:
  ListReceiver(Cache &cache, std::shared_ptr<RoomRepository> repository) : RoomReceiver(cache, repository) {}

  void Action() override
  {
    std::string session_id = GetSessionID();
    RetrieveRoomRequest request(session_id);
    RetrieveRoomResponse response = repository_->RetrieveRoom(request);
    cache_.SetRooms(response.GetRoomNames());
  }
};
#endif
