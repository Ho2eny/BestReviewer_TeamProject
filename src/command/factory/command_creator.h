#ifndef COMMAND_CREATOR_H_
#define COMMAND_CREATOR_H_

#include <memory>
#include "../login.h"
#include "../logout.h"
#include "../signup.h"
#include "../createchatroom.h"
#include "../joinchatroom.h"
#include "../listchatrooms.h"
#include "receiver_creator.h"

class CommandCreator
{
public:
    CommandCreator(Cache &cache) : cache_(cache) {}
    virtual ~CommandCreator(){};
    virtual std::unique_ptr<Command> CreateCommand(const CommandType &type, const std::string description) const = 0;

protected:
    Cache &cache_;
};

class UserCommandCreator : public CommandCreator
{
public:
    UserCommandCreator(Cache &cache) : CommandCreator(cache) {}

    std::unique_ptr<Command> CreateCommand(const CommandType &type, const std::string description) const override
    {
        ReceiverCreator *userReceiverCreator = new UserReceiverCreator(cache_);
        if (type == CommandType::kLogin)
            return move(make_unique<Login>(type, description, userReceiverCreator->CreateAReceiver(type)));

        if (type == CommandType::kSignup)
            return move(make_unique<Signup>(type, description, userReceiverCreator->CreateAReceiver(type)));

        if (type == CommandType::kLogout)
            return move(make_unique<Logout>(type, description, userReceiverCreator->CreateAReceiver(type)));

        throw InvalidCommandException("The command not supported (Command)");
    }
};

class RoomCommandCreator : public CommandCreator
{
public:
    RoomCommandCreator(Cache &cache) : CommandCreator(cache) {}

    std::unique_ptr<Command> CreateCommand(const CommandType &type, const std::string description) const override
    {
        ReceiverCreator *roomReceiverCreator = new RoomReceiverCreator(cache_);

        if (type == CommandType::kListRooms)
            return move(make_unique<ListChatRooms>(type, description, roomReceiverCreator->CreateAReceiver(type)));

        if (type == CommandType::kCreateRoom)
            return move(make_unique<CreateChatRoom>(type, description, roomReceiverCreator->CreateAReceiver(type)));

        throw InvalidCommandException("The command not supported (Command)");
    }
};

class ChatCommandCreator : public CommandCreator
{
public:
    ChatCommandCreator(Cache &cache) : CommandCreator(cache) {}

    std::unique_ptr<Command> CreateCommand(const CommandType &type, const std::string description) const override
    {
        ReceiverCreator *roomReceiverCreator = new ChatReceiverCreator(cache_);

        if (type == CommandType::kJoinRoom)
            return move(make_unique<JoinChatRoom>(type, description, roomReceiverCreator->CreateAReceiver(type)));

        throw InvalidCommandException("The command not supported (Command)");
    }
};

#endif