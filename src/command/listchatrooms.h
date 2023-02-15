#ifndef _LIST_CHAT_ROOMS_H_
#define _LIST_CHAT_ROOMS_H_

#include "./command.h"

class ListChatRooms : public Command
{
public:
    ListChatRooms(CommandType command_key, std::string description, Receiver *receiver)
        : Command(command_key, description, receiver) {}
};

#endif