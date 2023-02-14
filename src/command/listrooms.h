#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "./command.h"

class Login : public Command
{
public:
    Login(std::string command_key, std::string description)
        : Command(command_key, description) {}
    void Execute() const override;
};

#endif