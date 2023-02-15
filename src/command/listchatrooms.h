#ifndef LIST_CHAT_ROOMS_H_
#define LIST_CHAT_ROOMS_H_

#include <string>
#include <memory>
#include "./command.h"

class ListChatRooms : public Command
{
public:
    ListChatRooms(CommandType command_key, std::string description, std::unique_ptr<Receiver> receiver)
        : Command(command_key, description, move(receiver)) {}
};

#endif
