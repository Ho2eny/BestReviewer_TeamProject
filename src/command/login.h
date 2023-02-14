#ifndef LOGIN_H_
#define LOGIN_H_

#include <iostream>
#include <string>
#include "./command.h"
#include "./receiver/login_receiver.h"

class Login : public Command
{
public:
  Login(CommandType command_key, std::string description, Receiver *receiver)
      : Command(command_key, description, receiver) {}
};

#endif
