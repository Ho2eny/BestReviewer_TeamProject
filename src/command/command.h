#ifndef COMMAND_H_
#define COMMAND_H_

#include <curl/curl.h>
#include <json/json.h>
#include <string>
#include "./receiver.h"

std::string response = "";
class Command
{
public:
  Command(std::string command_key, std::string description) : command_key(command_key), description(description), receiver_(0) {}
  virtual ~Command() {}
  virtual void Execute() const = 0;
  bool HasData()
  {
    return receiver_ && receiver_->HasData();
  }
  std::string GetDescription() { return description; }
  std::string GetCommandKey() { return command_key; }
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
