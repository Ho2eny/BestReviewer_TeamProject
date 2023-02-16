#include "chat_http_repository.h"

#include "../../common/exception/chat/fail_parse_receive_message_reseponse_exception.h"
#include "../../common/exception/chat/fail_receive_message_exception.h"
#include "../../common/exception/chat/fail_send_message_exception.h"
// TODO(in.heo): curl_client를 Setter 주입받도록 수정
#include "../thirdparty/curl/curl_client.h"

ChatHttpRepository::ChatHttpRepository(std::string base_url) {
  Initialize();
}

ReceiveMessageResponse ChatHttpRepository::ReceiveMessage(const ReceiveMessageRequest& request) {
  Request http_request = chat_dto_converter_->ConvertToReceiveMessageHttpRequestFrom(request, base_url_);
  Response http_response = http_client_->Get(http_request);

  // TODO(in.heo): Replace this statement to Response::IsSuccess()
  if (http_response.GetStatusCode() >= 200 && http_response.GetStatusCode() < 300) {
    ReceiveMessageResponse response;
    try {
      response = chat_dto_converter_->ConvertToReceiveMessageResponseFrom(http_response);
    }
    catch (const BaseException& e) {
      // TODO(in.heo): Be better exception naming
      throw FailParseReceiveMessageResponseException(e.what());
    }

    return response;
  }

  throw FailReceiveMessageException(http_response.GetErrorMessage().c_str());
}

SendMessageResponse ChatHttpRepository::SendMessage(const SendMessageRequest& request) {
  Request http_request = chat_dto_converter_->ConvertToSendMessageHttpRequestFrom(request, base_url_);
  Response http_response = http_client_->Post(http_request);

  // TODO(in.heo): Replace this statement to Response::IsSuccess()
  if (http_response.GetStatusCode() >= 200 && http_response.GetStatusCode() < 300) {
    return SendMessageResponse();
  }

  throw FailSendMessageException(http_response.GetErrorMessage().c_str());
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
