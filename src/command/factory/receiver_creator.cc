#include "receiver_creator.h"

ReceiverCreator::ReceiverCreator(Cache &cache) : cache_(cache) {}
ReceiverCreator::~ReceiverCreator(){};

UserReceiverCreator::UserReceiverCreator(Cache &cache)
    : ReceiverCreator(cache) {}
std::unique_ptr<Receiver>
UserReceiverCreator::CreateAReceiver(const CommandType &type) const {
  std::shared_ptr<UserHttpRepository> user_repo =
      make_shared<UserHttpRepository>(cache_.GetValue(Cache::vBaseUrl));

  if (type == CommandType::kSignup)
    return move(make_unique<SignupReceiver>(cache_, user_repo));

  if (type == CommandType::kLogin)
    return move(make_unique<LoginReceiver>(cache_, user_repo));

  if (type == CommandType::kLogout)
    return move(make_unique<LogoutReceiver>(cache_, user_repo));

  throw InvalidCommandException("The command not supported");
}

RoomReceiverCreator::RoomReceiverCreator(Cache &cache)
    : ReceiverCreator(cache) {}
std::unique_ptr<Receiver>
RoomReceiverCreator::CreateAReceiver(const CommandType &type) const {
  std::shared_ptr<RoomHttpRepository> user_repo =
      make_shared<RoomHttpRepository>(cache_.GetValue(Cache::vBaseUrl));

  if (type == CommandType::kListRooms)
    return move(make_unique<ListReceiver>(cache_, user_repo));

  if (type == CommandType::kCreateRoom)
    return move(make_unique<CreateReceiver>(cache_, user_repo));

  throw InvalidCommandException("The command not supported");
}

ChatReceiverCreator::ChatReceiverCreator(Cache &cache)
    : ReceiverCreator(cache) {}
std::unique_ptr<Receiver>
ChatReceiverCreator::CreateAReceiver(const CommandType &type) const {
  std::shared_ptr<ChatHttpRepository> user_repo =
      make_shared<ChatHttpRepository>(cache_.GetValue(Cache::vBaseUrl));

  if (type == CommandType::kJoinRoom)
    return move(make_unique<JoinReceiver>(cache_, user_repo));

  throw InvalidCommandException("The command not supported");
}