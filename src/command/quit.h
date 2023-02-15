#ifndef LOGOUT_H_
#define LOGOUT_H_

#include <iostream>
#include <string>
#include "command.h"
#include "../ui_helper/ansi_color.h"

class Quit : public Command
{
public:
  Quit(std::string command_key, std::string description)
      : Command(command_key, description) {}

  bool Execute() const override
  {
    AnsiColor color;
    color.TextWithLineFeed("Bye.");
    return false;
  }
};

#endif
