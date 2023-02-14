#ifndef _JOIN_CHAT_ROOM_H_
#define _JOIN_CHAT_ROOM_H_

#include "./command.h"

class JoinChatRoom : public Command
{
public:
    JoinChatRoom(CommandType command_key, std::string description, Receiver *receiver)
        : Command(command_key, description, receiver) {}
    void Execute() const override {
        // TODO call JoinChattingRoom API
        std::cout << "join chat room" << std::endl;
    }
};

#endif