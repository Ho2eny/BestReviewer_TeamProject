#ifndef ROOM_RECEIVER_H_
#define ROOM_RECEIVER_H_

// TODO:: 모든 주석은 RoomRepository 들어오면 제거 하면 됨

#include <string>
#include "receiver.h"
#include "../../ui_helper/ansi_color.h"
// #include "../../interface/repository/room_repository.h"
// #include "../../interface/dto/chat/receive_message_request.h"
// #include "../../interface/dto/chat/receive_message_response.h"
// #include "../../interface/dto/chat/send_message_request.h"
// #include "../../interface/dto/chat/send_message_response.h"

#include "../../common/exception/command/invalid_command_exception.h"

#include "../../http/exception/network/authentication_failure_exception.h"
#include "../../http/exception/network/connection_failure_exception.h"
#include "../../http/exception/network/dns_resolving_failure_exception.h"
#include "../../http/exception/network/internal_exception.h"
#include "../../http/exception/network/general_network_exception.h"

class RoomReceiver : public Receiver
{
  // public:
  //   RoomReceiver(Cache &cache, std::shared_ptr<RoomRepository> repository) : Receiver(cache), repository_(repository) {}

protected:
  std::string GetSessionID()
  {
    if (cache_.GetValue(Cache::vSessionID).empty())
      throw InvalidCommandException("Session is not exists");
    return cache_.GetValue(Cache::vSessionID);
  }

  std::string GetRoomName()
  {
    if (!cache_.GetValue(Cache::vTestChatRoomName).empty())
      return cache_.GetValue(Cache::vTestChatRoomName);

    AnsiColor color;
    std::string chatRoomName;
    color.Important(" > Enter Chat Room Name: ");
    std::cin >> chatRoomName;
    return chatRoomName;
  }

  //   std::shared_ptr<RoomRepository> repository_;
};

#endif
