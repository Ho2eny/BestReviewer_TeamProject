#include "chat_http_repository.h"

#include "../converter/exception/base_json_exception.h"
#include "../exception/network/base_network_exception.h"
#include "../../common/exception/chat/fail_parse_receive_message_reseponse_exception.h"
#include "../../common/exception/chat/fail_receive_message_exception.h"
#include "../../common/exception/chat/fail_send_message_exception.h"
#include "../../common/exception/chat/invalid_chat_repository_exception.h"
// TODO(in.heo): curl_client를 Setter 주입받도록 수정
#include "../thirdparty/curl/curl_client.h"

ChatHttpRepository::ChatHttpRepository(std::string base_url) {
  Initialize();
}

ReceiveMessageResponse ChatHttpRepository::ReceiveMessage(const ReceiveMessageRequest& request) {
  if (!CheckPrecondition()) throw InvalidChatRepositoryException("Conveter or HttpClient is not valid");

  Request http_request = chat_dto_converter_->ConvertToReceiveMessageHttpRequestFrom(request, base_url_);

  try {
    Response http_response = http_client_->Get(http_request);

    if (http_response.IsSuccess()) {
      ReceiveMessageResponse response;
      response = chat_dto_converter_->ConvertToReceiveMessageResponseFrom(http_response);
      return response;
    }
    else {
      throw FailReceiveMessageException(http_response.GetErrorMessage().c_str());
    }
  }
  catch (const BaseNetworkException& e) {
    throw FailReceiveMessageException(e.what());
  }
  catch (const BaseJsonException& e) {
    throw FailParseReceiveMessageResponseException(e.what());
  }
}

SendMessageResponse ChatHttpRepository::SendMessage(const SendMessageRequest& request) {
  if (!CheckPrecondition()) throw InvalidChatRepositoryException("Conveter or HttpClient is not valid");

  Request http_request = chat_dto_converter_->ConvertToSendMessageHttpRequestFrom(request, base_url_);

  try {
    Response http_response = http_client_->Post(http_request);

    if (http_response.IsSuccess()) return SendMessageResponse();
    else throw FailSendMessageException(http_response.GetErrorMessage().c_str());
  }
  catch (const BaseNetworkException& e) {
    throw FailReceiveMessageException(e.what());
  }
}

void ChatHttpRepository::SetHttpClient(const std::shared_ptr<HttpPlugin>& client) {
  http_client_.reset();
  http_client_ = client;
}

void ChatHttpRepository::Initialize() {
  // TODO(in.heo): HARD_CODED curl_client를 Setter 주입받도록 수정
  CurlClient* curl_client = new CurlClient();
  http_client_ = std::shared_ptr<HttpPlugin>(curl_client);
  chat_dto_converter_ = std::make_shared<ChatDtoConverter>();
}

bool ChatHttpRepository::CheckPrecondition() const {
  return (http_client_ != nullptr && chat_dto_converter_ != nullptr);
}
