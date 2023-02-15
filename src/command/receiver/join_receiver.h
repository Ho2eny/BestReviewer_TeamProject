#ifndef JOIN_RECEIVER_H_
#define JOIN_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "receiver.h"
//#include "../../interface/dto/room/join_request.h"
//#include "../../interface/dto/room/join_response.h"
#include "../../utils.h"

class JoinReceiver : public Receiver
{
public:
  JoinReceiver(Cache &cache) : Receiver(cache) {}

  void Action() override
  {
    // JoinRequest request(sessionID, roomName);
    // Waiting for the implementatino from in.heo
    // JoinRoomResponse response = repository.JoinRoom(request);
    cache_.SetKV(Cache::SESSION_ID, "test_session_id");
  }

  std::string GetSessionID()
  {
    if (cache_.GetValue(Cache::SESSION_ID).length() > 0)
      return cache_.GetValue(Cache::SESSION_ID);

    std::string sessionID;
    std::cout << "Enter Session ID: ";
    std::cin >> sessionID;
    return sessionID;
  }

  std::string GetRoomName()
  {
    if (cache_.GetValue(Cache::CHAT_ROOM_NAME).length() > 0)
      return cache_.GetValue(Cache::CHAT_ROOM_NAME);

    std::string chatRoomName;
    std::cout << "Enter Chat Room Name: ";
    std::cin >> chatRoomName;
    return chatRoomName;
  }
};
#endif
