#ifndef JOIN_RECEIVER_H_
#define JOIN_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "room_receiver.h"

class JoinReceiver : public RoomReceiver
{
public:
  JoinReceiver(Cache &cache, std::shared_ptr<RoomRepository> repository) : RoomReceiver(cache, repository) {}

  void Action() override
  {
    // JoinRequest request(sessionID, roomName);
    // Waiting for the implementatino from in.heo
    // JoinRoomResponse response = repository.JoinRoom(request);
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
    if (std::find(rooms.begin(), rooms.end(), chat_room_name) == rooms.end())
      throw InvalidCommandException(std::string("The room name " + chat_room_name + " doesn't exist").c_str());

    return chat_room_name;
  }
};
#endif
