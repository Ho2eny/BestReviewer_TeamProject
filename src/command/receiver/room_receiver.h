#ifndef ROOM_RECEIVER_H_
#define ROOM_RECEIVER_H_

#include <string>
#include "receiver.h"
#include "../../ui_helper/ansi_color.h"
#include "../../interface/repository/room_repository.h"
#include "../../interface/dto/room/create_room_request.h"
#include "../../interface/dto/room/create_room_response.h"
#include "../../interface/dto/room/retrieve_room_request.h"
#include "../../interface/dto/room/retrieve_room_response.h"

#include "../../common/exception/command/invalid_command_exception.h"

class RoomReceiver : public Receiver
{
public:
  RoomReceiver(Cache &cache, std::shared_ptr<RoomRepository> repository) : Receiver(cache), repository_(repository) {}

protected:
  std::string GetSessionID()
  {
    if (cache_.GetValue(Cache::vSessionID).empty())
      throw InvalidCommandException("Session is not exists");
    return cache_.GetValue(Cache::vSessionID);
  }

  std::shared_ptr<RoomRepository> repository_;
};

#endif
