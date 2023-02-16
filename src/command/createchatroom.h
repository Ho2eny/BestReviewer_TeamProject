#ifndef CREATE_CHAT_ROOM_H_
#define CREATE_CHAT_ROOM_H_

#include <string>
#include <memory>
#include "command.h"

class CreateChatRoom : public Command
{
public:
    CreateChatRoom(CommandType command_key, std::string description, std::unique_ptr<Receiver> receiver)
        : Command(command_key, description, move(receiver)) {}
};

#endif
