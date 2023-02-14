#ifndef SIGNUP_H_
#define SIGNUP_H_

#include "./command.h"

class Signup : public Command
{
public:
    Signup(CommandType command_key, std::string description, Receiver *receiver)
        : Command(command_key, description, receiver) {}
    void Execute() const override;
};

#endif