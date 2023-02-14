#ifndef LOGIN_H_
#define LOGIN_H_

#include "./command.h"

class Login : public Command
{
public:
    Login(CommandType command_key, std::string description, Receiver *receiver)
        : Command(command_key, description, receiver) {}
    void Execute() const override;
};

#endif