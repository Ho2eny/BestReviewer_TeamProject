#ifndef CHAT_RECEIVER_H_
#define CHAT_RECEIVER_H_

// TODO:: 모든 주석은 ChatRepository 들어오면 제거 하면 됨

#include <string>
#include "receiver.h"
#include "../../ui_helper/ansi_color.h"
// #include "../../interface/repository/chat_repository.h"
// #include "../../interface/dto/chat/receive_message_request.h"
// #include "../../interface/dto/chat/receive_message_response.h"
// #include "../../interface/dto/chat/send_message_request.h"
// #include "../../interface/dto/chat/send_message_response.h"

class ChatReceiver : public Receiver
{
  // public:
  //   ChatReceiver(Cache &cache, std::shared_ptr<ChatRepository> repository) : Receiver(cache), repository_(repository) {}

  // protected:
  //   std::shared_ptr<ChatRepository> repository_;
};

#endif