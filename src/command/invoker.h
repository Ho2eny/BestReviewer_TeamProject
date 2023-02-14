#ifndef INVOKER_H_
#define INVOKER_H_

#include <memory>
#include <vector>
#include <json/json.h>
#include <stdexcept>
#include <algorithm>
#include "./command.h"

class Invoker
{
private:
  std::vector<Command *> on_invoke_;

public:
  ~Invoker() {}

  void SetOnInvoke(Command *command)
  {
    on_invoke_.push_back(command);
  }

  void Invoke(std::string command_key, Json::Value data)
  {
    std::cout << command_key << std::endl;
    for (auto it : on_invoke_)
    {
      if ((*it).GetCommandKey() == command_key)
      {
        if (!data.empty()) it->SetData(data);
        it->Execute();
        return;
      }
    }

    throw std::invalid_argument("Command not found");
  }

  void PrintCommands()
  {
    for (auto it : on_invoke_)
    {
      std::cout << it->GetCommandKey() << ". ";
      std::cout << it->GetDescription() << std::endl;
    }
  }
};

#endif
