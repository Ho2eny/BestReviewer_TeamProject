#ifndef CREATE_ROOM_REQUEST_H_
#define CREATE_ROOM_REQUEST_H_

#include <string>

#include "../base_request.h"

class CreateRoomRequest : public BaseRequest {
public:
  CreateRoomRequest() {}
  CreateRoomRequest(std::string room_name, std::string session_id) : room_name_(room_name), session_id_(session_id) {}

  std::string GetRoomName() const;
  std::string GetSessionId() const;

private:
  std::string room_name_;
  std::string session_id_;
};

inline std::string CreateRoomRequest::GetRoomName() const {
  return room_name_;
}

inline std::string CreateRoomRequest::GetSessionId() const {
  return session_id_;
}

#endif