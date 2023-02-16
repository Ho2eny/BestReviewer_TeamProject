#include "command_creator.h"

CommandCreator::CommandCreator(Cache &cache) : cache_(cache) {}
CommandCreator::~CommandCreator() {}

UserCommandCreator::UserCommandCreator(Cache &cache) : CommandCreator(cache) {}
std::unique_ptr<Command> UserCommandCreator::CreateCommand(const CommandType &type, const std::string description) const
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

RoomCommandCreator::RoomCommandCreator(Cache &cache) : CommandCreator(cache) {}
std::unique_ptr<Command> RoomCommandCreator::CreateCommand(const CommandType &type, const std::string description) const
{
    ReceiverCreator *roomReceiverCreator = new RoomReceiverCreator(cache_);

    if (type == CommandType::kListRooms)
        return move(make_unique<ListChatRooms>(type, description, roomReceiverCreator->CreateAReceiver(type)));

    if (type == CommandType::kCreateRoom)
        return move(make_unique<CreateChatRoom>(type, description, roomReceiverCreator->CreateAReceiver(type)));

    throw InvalidCommandException("The command not supported (Command)");
}

ChatCommandCreator::ChatCommandCreator(Cache &cache) : CommandCreator(cache) {}
std::unique_ptr<Command> ChatCommandCreator::CreateCommand(const CommandType &type, const std::string description) const
{
    ReceiverCreator *roomReceiverCreator = new ChatReceiverCreator(cache_);

    if (type == CommandType::kJoinRoom)
        return move(make_unique<JoinChatRoom>(type, description, roomReceiverCreator->CreateAReceiver(type)));

    throw InvalidCommandException("The command not supported (Command)");
}