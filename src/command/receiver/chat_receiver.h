#ifndef CHAT_RECEIVER_H_
#define CHAT_RECEIVER_H_

#include "receiver.h"
#include "../../ui_helper/ansi_color.h"
#include "../../interface/repository/chat_repository.h"
#include "../../interface/dto/chat/receive_message_request.h"
#include "../../interface/dto/chat/receive_message_response.h"
#include "../../interface/dto/chat/send_message_request.h"
#include "../../interface/dto/chat/send_message_response.h"

#include "../../common/exception/thread/fail_thread_attr_init.h"
#include "../../common/exception/thread/fail_thread_create.h"
#include "../../common/exception/thread/fail_thread_attr_destroy.h"
#include "../../common/exception/thread/fail_thread_join.h"

#include "../../common/exception/command/invalid_command_exception.h"

#include <string>
#include <memory>

class ChatReceiver : public Receiver
{
public:
  ChatReceiver(Cache &cache, std::shared_ptr<ChatRepository> repository) : Receiver(cache), repository_(repository) {}

protected:
  std::shared_ptr<ChatRepository> repository_;
};

#endif
