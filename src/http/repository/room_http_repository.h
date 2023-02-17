#ifndef ROOM_HTTP_REPOSITORY_H_
#define ROOM_HTTP_REPOSITORY_H_

#include <memory>
#include <string>

#include "../../interface/repository/room_repository.h"
#include "../converter/room_dto_converter.h"
#include "../http_plugin.h"

class RoomHttpRepository : public RoomRepository {
public:
  RoomHttpRepository(std::string base_url);

  virtual CreateRoomResponse CreateRoom(const CreateRoomRequest& request) override;

  virtual RetrieveRoomResponse RetrieveRoom(const RetrieveRoomRequest& request) override;

  void SetHttpClient(const std::shared_ptr<HttpPlugin>& client);

private:
  void Initialize();
  bool CheckPrecondition() const;

  std::shared_ptr<HttpPlugin> http_client_;
  std::shared_ptr<RoomDtoConverter> room_dto_converter_;
  std::string base_url_;
};

#endif