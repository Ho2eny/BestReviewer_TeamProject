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

  void SetOnInvoke(std::unique_ptr<Command> command);
  bool Invoke(std::string command_key);
  int PrintCommands();

private:
  std::vector<std::unique_ptr<Command>> on_invoke_;
  Cache &cache_;
};

#endif
