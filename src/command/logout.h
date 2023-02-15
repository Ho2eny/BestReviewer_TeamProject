#ifndef LOGOUT_H_
#define LOGOUT_H_

#include <iostream>
#include <string>
#include "./command.h"

class Logout : public Command
{
public:
  Logout(CommandType command_key, std::string description, Receiver *receiver)
      : Command(command_key, description, receiver) {}
};

#endif
