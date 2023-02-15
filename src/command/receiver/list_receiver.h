#ifndef LIST_RECEIVER_H_
#define LIST_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "receiver.h"
//#include "../../interface/dto/room/list_request.h"
//#include "../../interface/dto/room/list_response.h"
#include "../../utils.h"

class ListReceiver : public Receiver
{
public:
  ListReceiver(Cache &cache) : Receiver(cache) {}

  void Action() override
  {
    // ListRequest request(sessionID);
    // Waiting for the implementatino from in.heo
    // GetRoomList response = repository.getRoomList(request);
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
};
#endif
