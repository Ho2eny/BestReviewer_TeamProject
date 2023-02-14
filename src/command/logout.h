#ifndef LOGOUT_H_
#define LOGOUT_H_

#include "./command.h"

class Logout : public Command
{
public:
    Logout(CommandType command_key, std::string description)
        : Command(command_key, description) {}
    void Execute() const override;
};

#endif