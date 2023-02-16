#ifndef RECEIVER_CREATOR_H_
#define RECEIVER_CREATOR_H_

#include <memory>
#include "../command_type.h"

#include "../receiver/login_receiver.h"
#include "../receiver/signup_receiver.h"
#include "../receiver/logout_receiver.h"
#include "../receiver/create_receiver.h"
#include "../receiver/list_receiver.h"
#include "../receiver/join_receiver.h"

#include "../../interface/repository/user_repository.h"
#include "../../interface/repository/room_repository.h"
#include "../../interface/repository/chat_repository.h"

#include "../../http/repository/user_http_repository.h"
#include "../../http/repository/room_http_repository.h"
#include "../../http/repository/chat_http_repository.h"

#include "../../common/exception/command/invalid_command_exception.h"

class ReceiverCreator
{
public:
    ReceiverCreator(Cache &cache) : cache_(cache) {}
    virtual ~ReceiverCreator(){};
    virtual std::unique_ptr<Receiver> CreateAReceiver(const CommandType &type) const = 0;

protected:
    Cache &cache_;
};

class UserReceiverCreator : public ReceiverCreator
{
public:
    UserReceiverCreator(Cache &cache) : ReceiverCreator(cache) {}
    std::unique_ptr<Receiver> CreateAReceiver(const CommandType &type) const override
    {
        std::shared_ptr<UserHttpRepository> user_repo = make_shared<UserHttpRepository>(cache_.GetValue(Cache::vBaseUrl));

        if (type == CommandType::kSignup)
            return move(make_unique<SignupReceiver>(cache_, user_repo));

        if (type == CommandType::kLogin)
            return move(make_unique<LoginReceiver>(cache_, user_repo));

        if (type == CommandType::kLogout)
            return move(make_unique<LogoutReceiver>(cache_, user_repo));

        throw InvalidCommandException("The command not supported");
    }
};


class RoomReceiverCreator : public ReceiverCreator
{
public:
    RoomReceiverCreator(Cache &cache) : ReceiverCreator(cache) {}
    std::unique_ptr<Receiver> CreateAReceiver(const CommandType &type) const override
    {
        std::shared_ptr<RoomHttpRepository> user_repo = make_shared<RoomHttpRepository>(cache_.GetValue(Cache::vBaseUrl));

        if (type == CommandType::kListRooms)
            return move(make_unique<ListReceiver>(cache_, user_repo));

        if (type == CommandType::kCreateRoom)
            return move(make_unique<CreateReceiver>(cache_, user_repo));

        throw InvalidCommandException("The command not supported");
    }
};

class ChatReceiverCreator : public ReceiverCreator
{
public:
    ChatReceiverCreator(Cache &cache) : ReceiverCreator(cache) {}
    std::unique_ptr<Receiver> CreateAReceiver(const CommandType &type) const override
    {
        std::shared_ptr<ChatHttpRepository> user_repo = make_shared<ChatHttpRepository>(cache_.GetValue(Cache::vBaseUrl));

        if (type == CommandType::kJoinRoom)
            return move(make_unique<JoinReceiver>(cache_, user_repo));

        throw InvalidCommandException("The command not supported");
    }
};

#endif