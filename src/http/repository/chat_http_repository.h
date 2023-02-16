#ifndef CHAT_HTTP_REPOSITORY_H_
#define CHAT_HTTP_REPOSITORY_H_

#include "../../interface/repository/chat_repository.h"
#include "../converter/chat_dto_converter.h"
#include "../http_plugin.h"

class ChatHttpRepository : public ChatRepository {
public:
  ChatHttpRepository(std::string base_url);

  virtual ReceiveMessageResponse ReceiveMessage(const ReceiveMessageRequest& request) override;

  virtual SendMessageResponse SendMessage(const SendMessageRequest& request) override;

  void SetHttpClient(const std::shared_ptr<HttpPlugin>& client);

private:
  void Initialize();

  std::shared_ptr<HttpPlugin> http_client_;
  std::shared_ptr<ChatDtoConverter> chat_dto_converter_;
  std::string base_url_;
};

#endif
