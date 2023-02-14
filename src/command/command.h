#ifndef COMMAND_H_
#define COMMAND_H_

#include <algorithm>
#include <string>
#include "./receiver/receiver.h"
#include "./command_type.h"

class Command
{
public:
  Command(std::string command_key, std::string description, Receiver *receiver = nullptr)
      : command_key_(command_key), description_(description), receiver_(receiver), base_url_("")
  {
    std::transform(command_key_.begin(), command_key_.end(), command_key_.begin(), ::tolower);
  }

  Command(CommandType command_key, std::string description, Receiver *receiver = nullptr)
      : Command(std::to_string(static_cast<int>(command_key)), description, receiver)
  {
  }
  virtual ~Command() {}

  virtual bool Execute() const
  {
    if (receiver_)
      receiver_->Action();

    return true;
  }

  std::string GetDescription()
  {
    return description_;
  }

  std::string GetCommandKey()
  {
    return command_key_;
  }

  void SetBaseUrl(std::string base_url)
  {
    base_url_ = base_url;
  }

protected:
  std::string command_key_;
  std::string description_;
  Receiver *receiver_;
  std::string base_url_;
};

#endif
