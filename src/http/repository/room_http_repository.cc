#include "room_http_repository.h"

#include "../converter/exception/base_json_exception.h"
#include "../exception/network/base_network_exception.h"
#include "../../common/exception/room/fail_create_room_exception.h"
#include "../../common/exception/room/fail_parse_retrieve_room_response_exception.h"
#include "../../common/exception/room/fail_retrieve_room_exception.h"
#include "../../common/exception/room/invalid_room_repository_exception.h"
#include "../thirdparty/curl/curl_client.h"

RoomHttpRepository::RoomHttpRepository(std::string base_url) : base_url_(base_url) {
  Initialize();
}

CreateRoomResponse RoomHttpRepository::CreateRoom(const CreateRoomRequest& request) {
  if (!CheckPrecondition()) throw InvalidRoomRepositoryException("Conveter or HttpClient is not valid");

  Request http_request = room_dto_converter_->ConvertToCreateRoomHttpRequestFrom(request, base_url_);

  try {
    Response http_response = http_client_->Post(http_request);
    if (http_response.IsSuccess()) return CreateRoomResponse();
    else throw FailCreateRoomException(http_response.GetBody().c_str());

  }
  catch (const BaseNetworkException& e) {
    throw FailCreateRoomException(e.what());
  }

}

RetrieveRoomResponse RoomHttpRepository::RetrieveRoom(const RetrieveRoomRequest& request) {
  if (!CheckPrecondition()) throw InvalidRoomRepositoryException("Conveter or HttpClient is not valid");

  Request http_request = room_dto_converter_->ConvertToRetrieveRoomHttpRequestFrom(request, base_url_);

  try {
    Response http_response = http_client_->Get(http_request);
    if (http_response.IsSuccess()) {
      RetrieveRoomResponse response;
      response = room_dto_converter_->ConvertToRetrieveRoomResponseFrom(http_response);
      return response;
    }
    else {
      throw FailRetrieveRoomException(http_response.GetBody().c_str());
    }
  }
  catch (const BaseNetworkException& e) {
    throw FailRetrieveRoomException(e.what());
  }
  catch (const BaseJsonException& e) {
    throw FailParseRetrieveRoomResponseException(e.what());
  }
}

void RoomHttpRepository::SetHttpClient(const std::shared_ptr<HttpPlugin>& client) {
  http_client_.reset();
  http_client_ = client;
}

void RoomHttpRepository::Initialize() {
  CurlClient* curl_client = new CurlClient();
  http_client_ = std::shared_ptr<HttpPlugin>(curl_client);
  room_dto_converter_ = std::make_shared<RoomDtoConverter>();
}

bool RoomHttpRepository::CheckPrecondition() const {
  if (http_client_ == nullptr || room_dto_converter_ == nullptr) return false;
  return true;
}
