#ifndef JOIN_CHAT_ROOM_H_
#define JOIN_CHAT_ROOM_H_

#include <string>
#include <memory>
#include "command.h"

class JoinChatRoom : public Command
{
public:
    JoinChatRoom(CommandType command_key, std::string description, std::unique_ptr<Receiver> receiver)
        : Command(command_key, description, move(receiver)) {}
};

#endif
