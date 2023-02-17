#ifndef CHAT_REPOSITORY_H_
#define CHAT_REPOSITORY_H_

#include "../dto/chat/receive_message_request.h"
#include "../dto/chat/receive_message_response.h"
#include "../dto/chat/send_message_request.h"
#include "../dto/chat/send_message_response.h"

class ChatRepository {
public:
  virtual ReceiveMessageResponse ReceiveMessage(const ReceiveMessageRequest& request) = 0;

  virtual SendMessageResponse SendMessage(const SendMessageRequest& request) = 0;
};

#endif
