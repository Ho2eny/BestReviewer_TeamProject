#ifndef RECEIVE_MESSAGE_RESPONSE_H_
#define RECEIVE_MESSAGE_RESPONSE_H_

#include "../base_response.h"

#include <vector>

#include "./message.h"

class ReceiveMessageResponse : public BaseResponse {
public:
  ReceiveMessageResponse() {}
  ReceiveMessageResponse(std::vector<Message> messages) : messages_(messages) {}

  std::vector<Message> GetMessages() const;
private:
  std::vector<Message> messages_;
};

inline std::vector<Message> ReceiveMessageResponse::GetMessages() const {
  return messages_;
}

#endif
