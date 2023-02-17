#ifndef COMMAND_CREATOR_H_
#define COMMAND_CREATOR_H_

#include "../../common/exception/command/invalid_command_exception.h"
#include "../createchatroom.h"
#include "../joinchatroom.h"
#include "../listchatrooms.h"
#include "../login.h"
#include "../logout.h"
#include "../signup.h"
#include "receiver_creator.h"
#include <memory>

class CommandCreator {
public:
  CommandCreator(Cache &cache);
  virtual ~CommandCreator();
  virtual std::unique_ptr<Command>
  CreateCommand(const CommandType &type,
                const std::string description) const = 0;

protected:
  Cache &cache_;
};

class UserCommandCreator : public CommandCreator {
public:
  UserCommandCreator(Cache &cache);
  std::unique_ptr<Command>
  CreateCommand(const CommandType &type,
                const std::string description) const override;
};

class RoomCommandCreator : public CommandCreator {
public:
  RoomCommandCreator(Cache &cache);
  std::unique_ptr<Command>
  CreateCommand(const CommandType &type,
                const std::string description) const override;
};

class ChatCommandCreator : public CommandCreator {
public:
  ChatCommandCreator(Cache &cache);
  std::unique_ptr<Command>
  CreateCommand(const CommandType &type,
                const std::string description) const override;
};

#endif