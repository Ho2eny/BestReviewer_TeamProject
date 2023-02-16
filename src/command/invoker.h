#ifndef INVOKER_H_
#define INVOKER_H_

#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "command.h"
#include "cache.h"
#include "../ui_helper/ansi_color.h"

class Invoker
{
public:
  Invoker(Cache &cache) : cache_(cache) {}
  ~Invoker() {}

  void SetOnInvoke(std::unique_ptr<Command> command)
  {
    on_invoke_.push_back(move(command));
  }

  bool Invoke(std::string command_key)
  {
    std::string lower_command_key = command_key;
    std::transform(lower_command_key.begin(), lower_command_key.end(), lower_command_key.begin(), ::tolower);
    for (const auto &it : on_invoke_)
    {
      if ((*it).GetCommandKey() == lower_command_key) 
        return it->Execute();
    }

    throw InvalidCommandException("Command not found");
  }

  void PrintCommands()
  {
    AnsiColor color;
    color.TextWithLineFeed("\nMENU");
    for (const auto &it : on_invoke_)
    {
      color.Important("> " + it->GetCommandKey() + ". ");
      color.TextWithLineFeed(it->GetDescription());
    }
  }

  void SetBaseUrl(std::string base_url)
  {
    cache_.SetBaseUrl(base_url);
  }

private:
  std::vector<std::unique_ptr<Command>> on_invoke_;
  Cache &cache_;
};

#endif
