#ifndef RECEIVE_MESSAGE_REQUEST_H_
#define RECEIVE_MESSAGE_REQUEST_H_

#include <string>

#include "../base_request.h"

class ReceiveMessageRequest : public BaseRequest {
public:
  ReceiveMessageRequest() {}
  ReceiveMessageRequest(std::string room_name, std::string session_id) : room_name_(room_name), session_id_(session_id) {}

  std::string GetRoomName() const;
  std::string GetSessionId() const;

private:
  std::string room_name_;
  std::string session_id_;
};

inline std::string ReceiveMessageRequest::GetRoomName() const {
  return room_name_;
}

inline std::string ReceiveMessageRequest::GetSessionId() const {
  return session_id_;
}

#endif