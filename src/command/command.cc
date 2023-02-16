#include "command.h"

Command::Command(std::string command_key, std::string description, std::unique_ptr<Receiver> receiver)
    : command_key_(command_key), description_(description), receiver_(move(receiver))
{
  std::transform(command_key_.begin(), command_key_.end(), command_key_.begin(), ::tolower);
}

Command::Command(CommandType command_key, std::string description, std::unique_ptr<Receiver> receiver)
    : Command(std::to_string(static_cast<int>(command_key)), description, move(receiver)) {}

bool Command::Execute() const
{
  if (!receiver_)
    return true;

  try
  {
    receiver_->Action();
  }
  catch (const InvalidCommandException &ex)
  {
    throw InvalidCommandException(ex.what());
  }

  return true;
}

std::string Command::GetDescription() const
{
  return description_;
}

std::string Command::GetCommandKey()
{
  return command_key_;
}
