#ifndef RECEIVER_H_
#define RECEIVER_H_
#include <string>
#include <json/json.h>

class Receiver
{
private:
  Json::Value data;

public:
  Receiver() : data(Json::objectValue) {}
  Receiver(Json::Value data) : data(data) {}
  Json::Value GetData()
  {
    return data;
  }
  void SetData(Json::Value data) { this->data = data; }
  bool HasData() { return !data.empty(); }
  Json::Value GetData(std::string key)
  {
    return data;
  }
};

#endif
