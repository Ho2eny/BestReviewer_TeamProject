#ifndef CREATE_RECEIVER_H_
#define CREATE_RECEIVER_H_

#include <iostream>
#include <memory>
#include <algorithm>
#include "../cache.h"
#include "room_receiver.h"
#include "../../common/exception/room/fail_create_room_exception.h"

class CreateReceiver : public RoomReceiver
{
public:
  CreateReceiver(Cache &cache, std::shared_ptr<RoomRepository> repository) : RoomReceiver(cache, repository) {}

  void Action() override
  {
    std::string room_name = GetRoomName();
    std::string session_id = GetSessionID();
    CreateRoomRequest request(room_name, session_id);
    try {
      CreateRoomResponse response = repository_->CreateRoom(request);
      cache_.SetRoomName(room_name);
    }
    catch (const FailCreateRoomException &ex)
    {
      throw InvalidCommandException(ex.what());
    }
  }

  std::string GetRoomName()
  {
    if (!cache_.GetValue(Cache::vTestChatRoomName).empty())
      return cache_.GetValue(Cache::vTestChatRoomName);

    AnsiColor color;
    std::string chat_room_name;
    color.Important(" > Enter Chat Room Name: ");
    std::cin >> chat_room_name;

    std::vector<std::string> rooms = cache_.GetRooms();
    if (std::find(rooms.begin(), rooms.end(), chat_room_name) != rooms.end())
      throw InvalidCommandException(std::string("The room name " + chat_room_name + " already exist").c_str());

    return chat_room_name;
  }
};
#endif
