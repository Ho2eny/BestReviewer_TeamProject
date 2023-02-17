#ifndef COMMAND_H_
#define COMMAND_H_

#include <algorithm>
#include <string>
#include <memory>
#include <iostream>
#include "receiver/receiver.h"
#include "command_type.h"
#include "../common/exception/command/invalid_command_exception.h"

class Command
{
public:
  Command(std::string command_key, std::string description, std::unique_ptr<Receiver> receiver = nullptr);
  Command(CommandType command_key, std::string description, std::unique_ptr<Receiver> receiver = nullptr);

  virtual ~Command() {}

  virtual bool Execute() const;

  std::string GetDescription() const;

  std::string GetCommandKey();

protected:
  std::string command_key_;
  std::string description_;
  std::unique_ptr<Receiver> receiver_;
};

#endif
