#ifndef COMMAND_H_
#define COMMAND_H_

#include <algorithm>
#include <string>
#include <memory>
#include <iostream>
#include "receiver/receiver.h"
#include "command_type.h"
#include "../common/exception/command/invalid_command_exception.h"
#include "../http/exception/network/general_network_exception.h"

class Command
{
public:
  Command(std::string command_key, std::string description, std::unique_ptr<Receiver> receiver = nullptr)
      : command_key_(command_key), description_(description), receiver_(move(receiver))
  {
    std::transform(command_key_.begin(), command_key_.end(), command_key_.begin(), ::tolower);
  }

  Command(CommandType command_key, std::string description, std::unique_ptr<Receiver> receiver = nullptr)
      : Command(std::to_string(static_cast<int>(command_key)), description, move(receiver)) {}

  virtual ~Command() {}

  virtual bool Execute() const
  {
    if (!receiver_)
      return true;

    try
    {
      receiver_->Action();
    }
    catch (const GeneralNetworkException &ex)
    {
      throw GeneralNetworkException(ex.what());
    }
    catch (const InvalidCommandException &ex)
    {
      throw InvalidCommandException(ex.what());
    }

    return true;
  }

  std::string GetDescription() const
  {
    return description_;
  }

  std::string GetCommandKey()
  {
    return command_key_;
  }

protected:
  std::string command_key_;
  std::string description_;
  std::unique_ptr<Receiver> receiver_;
};

#endif
