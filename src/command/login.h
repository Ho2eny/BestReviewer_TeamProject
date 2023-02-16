#ifndef LOGIN_H_
#define LOGIN_H_

#include <string>
#include <memory>
#include "command.h"

class Login : public Command
{
public:
  Login(CommandType command_key, std::string description, std::unique_ptr<Receiver> receiver)
      : Command(command_key, description, move(receiver)) {}
};

#endif
