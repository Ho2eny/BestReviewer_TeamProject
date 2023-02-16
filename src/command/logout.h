#ifndef LOGOUT_H_
#define LOGOUT_H_

#include <memory>
#include <string>
#include "./command.h"

class Logout : public Command
{
public:
  Logout(CommandType command_key, std::string description, std::unique_ptr<Receiver> receiver)
      : Command(command_key, description, move(receiver)) {}
};

#endif
