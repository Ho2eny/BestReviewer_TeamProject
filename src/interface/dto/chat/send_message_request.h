#ifndef SEND_MESSAGE_REQUEST_H_
#define SEND_MESSAGE_REQUEST_H_

#include <string>

#include "../base_request.h"

class SendMessageRequest : public BaseRequest {
public:
  SendMessageRequest() {}
  SendMessageRequest(std::string room_name, std::string session_id, std::string message) : room_name_(room_name), session_id_(session_id), message_(message) {}

  std::string GetRoomName() const;
  std::string GetSessionId() const;
  std::string GetMessage() const;

private:
  std::string room_name_;
  std::string session_id_;
  std::string message_;
};

inline std::string SendMessageRequest::GetRoomName() const {
  return room_name_;
}

inline std::string SendMessageRequest::GetSessionId() const {
  return session_id_;
}

inline std::string SendMessageRequest::GetMessage() const {
  return message_;
}
#endif