#ifndef _CREATE_CHAT_ROOM_H_
#define _CREATE_CHAT_ROOM_H_

#include "./command.h"

class CreateChatRoom : public Command
{
public:
    CreateChatRoom(CommandType command_key, std::string description, Receiver *receiver)
        : Command(command_key, description, receiver) {}
    void Execute() const override {
        // TODO call CreateChatRoom API
        std::cout << "create chat room" << std::endl;
    }
};

#endif