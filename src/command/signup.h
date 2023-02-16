#ifndef SIGNUP_H_
#define SIGNUP_H_

#include <memory>
#include <string>
#include "command.h"

class Signup : public Command
{
public:
  Signup(CommandType command_key, std::string description, std::unique_ptr<Receiver> receiver)
      : Command(command_key, description, move(receiver)) {}
};

#endif
