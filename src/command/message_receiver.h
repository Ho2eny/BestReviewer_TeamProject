#ifndef JSON_COMPOSER_H_
#define JSON_COMPOSER_H_
#include <string>

class MessageReceiver
{
private:
  std::string message;

public:
  MessageReceiver(std ::string message) : message(message) {}
  void SetMessage(std::string message)
  {
    this->message = message;
  }
  std::string GetMessage()
  {
    return message;
  }
};

#endif
