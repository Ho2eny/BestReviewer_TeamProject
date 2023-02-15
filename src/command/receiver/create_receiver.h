#ifndef CREATE_RECEIVER_H_
#define CREATE_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "receiver.h"
//#include "../../interface/dto/room/create_request.h"
//#include "../../interface/dto/room/create_response.h"
#include "../../utils.h"

class CreateReceiver : public Receiver
{
public:
  CreateReceiver(Cache &cache) : Receiver(cache) {}

  void Action() override
  {
    // CreateRequest request(sessionID, roomName);
    // Waiting for the implementatino from in.heo
    // CreateRoomResponse response = repository.CreateRoom(request);
  }

  std::string GetSessionID()
  {
    if (cache_.GetValue(Cache::vSessionID).length() > 0)
      return cache_.GetValue(Cache::vSessionID);

    std::string sessionID;
    std::cout << "Enter Session ID: ";
    std::cin >> sessionID;
    return sessionID;
  }

  std::string GetRoomName()
  {
    if (cache_.GetValue(Cache::vChatRoomName).length() > 0)
      return cache_.GetValue(Cache::vChatRoomName);

    std::string chatRoomName;
    std::cout << "Enter Chat Room Name: ";
    std::cin >> chatRoomName;
    return chatRoomName;
  }
};
#endif
