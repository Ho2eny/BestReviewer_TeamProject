#ifndef COMMAND_H_
#define COMMAND_H_

#include <curl/curl.h>
#include <string>
#include "./message_receiver.h"

std::string response = "";
class Command
{
protected:
  bool require_message;
  MessageReceiver *receiver_;

public:
  Command() : require_message(false), receiver_(0) {}
  virtual ~Command() {}
  virtual void Execute() const = 0;
  bool RequireMessage()
  {
    return require_message;
  }
  void SetReceiverString(std::string message)
  {
    if (receiver_)
    {
      receiver_->SetMessage(message);
    }
  }
};

static size_t curl_callback_(void *contents, size_t size, size_t nmemb, void *userp)
{
  char *str = static_cast<char *>(contents);
  size_t realsize = size * nmemb;
  std::string &res = *(static_cast<std::string *>(userp));
  res.append(str, realsize);
  return realsize;
}

class SimpleWelcomCommand : public Command
{
private:
public:
  explicit SimpleWelcomCommand() {}
  void Execute() const override
  {
    CURL *curl;

    long responseCode;

    response.clear();

    /*TODO
      - curl 을 사용하는 과정이 계속 반복되는데 좋은 코드 품질을 가지도록 구현해보세요.
      - 서버의 동작여부와 상관 없이 Client 의 기능이 잘 동작한다는 것을 보장하는 테스트를 만들어 보세요.
    */
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
private:
public:
  explicit ChatParseSimpleJsonCommand() {}
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
  explicit JsonComposeCommand(MessageReceiver *receiver)
  {
    receiver_ = receiver;
    require_message = true;
  }
  void Execute() const override
  {
    Json::Value root;

    root["message"] = receiver_->GetMessage().c_str();

    std::cout << root["message"].asString() << std::endl;

    Json::StreamWriterBuilder jsonBuilder;
    std::string jsonStr = Json::writeString(jsonBuilder, root);
    std::cout << jsonStr << std::endl;
  }
};

#endif
