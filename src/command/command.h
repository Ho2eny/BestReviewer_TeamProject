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

static size_t curl_callback_(void *contents, size_t size, size_t nmemb, void *userp)
{
  char *str = static_cast<char *>(contents);
  size_t realsize = size * nmemb;
  std::string &res = *(static_cast<std::string *>(userp));
  res.append(str, realsize);
  return realsize;
}

class SimpleWelcomeCommand : public Command
{
public:
  explicit SimpleWelcomeCommand(std::string command_key, std::string description) : Command(command_key, description) {}
  void Execute() const override
  {
    CURL *curl;

    long responseCode;
    response.clear();

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:34568/chat/welcome_simpleJson");
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback_);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK)
    {
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
      std::cout << "OK to curl : " << responseCode << ", " << response << std::endl
                << std::endl;
    }
    else
    {
      std::cout << "error response : " << res << std::endl
                << std::endl;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
  }
};

class ChatParseSimpleJsonCommand : public Command
{
public:
  explicit ChatParseSimpleJsonCommand(std::string command_key, std::string description) : Command(command_key, description) {}
  void Execute() const override
  {
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();
    Json::Value root;
    std::string errors;

    std::cout << response << std::endl;
    bool result = reader->parse(response.c_str(), response.c_str() + response.size(), &root, &errors);
    delete reader;

    std::cout << root["message"].asString() << std::endl;
  }
};

class JsonComposeCommand : public Command
{
public:
  explicit JsonComposeCommand(std::string command_key, std::string description, Receiver *receiver) : Command(command_key, description)
  {
    receiver_ = receiver;
  }
  void Execute() const override
  {
    Json::Value root;

    root["message"] = receiver_->GetData()["message"];

    std::cout << root["message"].asString() << std::endl;

    Json::StreamWriterBuilder jsonBuilder;
    std::string jsonStr = Json::writeString(jsonBuilder, root);
    std::cout << jsonStr << std::endl;
  }
};

#endif
