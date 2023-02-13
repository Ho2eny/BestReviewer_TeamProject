#ifndef INVOKER_H_
#define INVOKER_H_

#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "./command.h"

#define Comman

class Invoker
{
private:
  std::vector<std::pair<std::string, Command *>> on_invoke_;

public:
  ~Invoker() {}

  void SetOnInvoke(std::string command_key, Command *command)
  {
    on_invoke_.push_back(make_pair(command_key, command));
  }

  void Invoke(std::string command_key, std::string message)
  {
    std::cout << command_key << std::endl;
    auto it = std::find_if(on_invoke_.begin(), on_invoke_.end(), [&command_key](const std::pair<std::string, Command *> &command)
                           { return command.first == command_key; });
    if (it == on_invoke_.end())
    {
      throw std::invalid_argument("Command not found");
    }

    if (message.length() > 0 && it->second->RequireMessage())
    {
      it->second->SetReceiverString(message);
    }

    it->second->Execute();
  }
};

#endif
