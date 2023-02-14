#ifndef COMMAND_H_
#define COMMAND_H_

#include <curl/curl.h>
#include <json/json.h>
#include <string>
#include "./receiver.h"
#include "./command_type.h"

class Command
{
public:
  Command(CommandType command_key, std::string description, Receiver* receiver = nullptr) 
    : command_key(std::to_string(static_cast<int>(command_key))), description(description), receiver_(receiver) {}
  virtual ~Command() {}
  virtual void Execute() const = 0;
  bool HasData()
  {
    return receiver_ && receiver_->HasData();
  }
  std::string GetDescription() {
    return description; }
  std::string GetCommandKey() {
    return command_key; }
  void SetData(Json::Value &data)
  {
    if (receiver_)
    {
      receiver_->SetData(data);
    }
  }

protected:
  std::string command_key;
  std::string description;
  Receiver *receiver_;
};

#endif
