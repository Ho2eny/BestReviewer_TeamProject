#ifndef LOGOUT_H_
#define LOGOUT_H_

#include <iostream>
#include <string>
#include "./command.h"

class Quit : public Command
{
public:
  Quit(std::string command_key, std::string description)
      : Command(command_key, description) {}

  bool Execute() const override
  {
    return false;
  }
};

#endif
