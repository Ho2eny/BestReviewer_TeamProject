#ifndef RECEIVER_CREATOR_H_
#define RECEIVER_CREATOR_H_

#include "../command_type.h"
#include <memory>

#include "../receiver/create_receiver.h"
#include "../receiver/join_receiver.h"
#include "../receiver/list_receiver.h"
#include "../receiver/login_receiver.h"
#include "../receiver/logout_receiver.h"
#include "../receiver/signup_receiver.h"

#include "../../interface/repository/chat_repository.h"
#include "../../interface/repository/room_repository.h"
#include "../../interface/repository/user_repository.h"

#include "../../http/repository/chat_http_repository.h"
#include "../../http/repository/room_http_repository.h"
#include "../../http/repository/user_http_repository.h"

#include "../../common/exception/command/invalid_command_exception.h"

class ReceiverCreator {
public:
  ReceiverCreator(Cache &cache);
  virtual ~ReceiverCreator();
  virtual std::unique_ptr<Receiver>
  CreateAReceiver(const CommandType &type) const = 0;

protected:
  Cache &cache_;
};

class UserReceiverCreator : public ReceiverCreator {
public:
  UserReceiverCreator(Cache &cache);
  std::unique_ptr<Receiver>
  CreateAReceiver(const CommandType &type) const override;
};

class RoomReceiverCreator : public ReceiverCreator {
public:
  RoomReceiverCreator(Cache &cache);
  std::unique_ptr<Receiver>
  CreateAReceiver(const CommandType &type) const override;
};

class ChatReceiverCreator : public ReceiverCreator {
public:
  ChatReceiverCreator(Cache &cache);
  std::unique_ptr<Receiver>
  CreateAReceiver(const CommandType &type) const override;
};

#endif