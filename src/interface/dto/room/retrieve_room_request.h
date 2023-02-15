#ifndef RETRIEVE_ROOM_REQUEST_H_
#define RETRIEVE_ROOM_REQUEST_H_

#include <string>

#include "../base_request.h"

class RetrieveRoomRequest : public BaseRequest {
public:
  RetrieveRoomRequest() {}
  RetrieveRoomRequest(std::string session_id) : session_id_(session_id) {}

  std::string GetSessionId() const;

private:
  std::string session_id_;
};

inline std::string RetrieveRoomRequest::GetSessionId() const {
  return session_id_;
}

#endif