#ifndef RETRIEVE_ROOM_RESPONSE_H_
#define RETRIEVE_ROOM_RESPONSE_H_

#include <string>
#include <vector>

#include "../base_response.h"

class RetrieveRoomResponse : public BaseResponse {
public:
  RetrieveRoomResponse() {}
  RetrieveRoomResponse(std::vector<std::string>& room_names) : room_names_(room_names) {}

  std::vector<std::string> GetRoomNames() const;

private:
  std::vector<std::string> room_names_;
};

inline std::vector<std::string> RetrieveRoomResponse::GetRoomNames() const {
  return room_names_;
}

#endif
