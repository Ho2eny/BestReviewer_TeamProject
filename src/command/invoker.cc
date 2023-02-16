#include "invoker.h"

void Invoker::SetOnInvoke(std::unique_ptr<Command> command)
{
  on_invoke_.push_back(move(command));
}

bool Invoker::Invoke(std::string command_key)
{
  std::string lower_command_key = command_key;
  std::transform(lower_command_key.begin(), lower_command_key.end(), lower_command_key.begin(), ::tolower);
  for (const auto &it : on_invoke_)
  {
    if ((*it).GetCommandKey() == lower_command_key)
    {
      try
      {
        return it->Execute();
      }
      catch (const InvalidCommandException &ex)
      {
        throw InvalidCommandException(ex.what());
      }
    }
  }

  throw InvalidCommandException("Command not found");
}

int Invoker::PrintCommands()
{
  AnsiColor color;
  color.TextWithLineFeed("\nMENU");
  for (const auto &it : on_invoke_)
  {
    color.Important("> " + it->GetCommandKey() + ". ");
    color.TextWithLineFeed(it->GetDescription());
  }

  return on_invoke_.size();
}