#include "room_http_repository.h"

#include "../../common/exception/room/fail_create_room_exception.h"
#include "../../common/exception/room/fail_parse_retrieve_room_response_exception.h"
#include "../../common/exception/room/fail_retrieve_room_exception.h"
#include "../thirdparty/curl/curl_client.h"

RoomHttpRepository::RoomHttpRepository(std::string base_url) : base_url_(base_url) {
  Initialize();
}

CreateRoomResponse RoomHttpRepository::CreateRoom(const CreateRoomRequest& request) {
  Request http_request = room_dto_converter_->ConvertToCreateRoomHttpRequestFrom(request, base_url_);
  Response http_response = http_client_->Post(http_request);

  if (http_response.IsSuccess()) return CreateRoomResponse();

  throw FailCreateRoomException(http_response.GetErrorMessage().c_str());
}

RetrieveRoomResponse RoomHttpRepository::RetrieveRoom(const RetrieveRoomRequest& request) {
  Request http_request = room_dto_converter_->ConvertToRetrieveRoomHttpRequestFrom(request, base_url_);
  Response http_response = http_client_->Get(http_request);

  if (http_response.IsSuccess()) {
    RetrieveRoomResponse response;

    try {
      response = room_dto_converter_->ConvertToRetrieveRoomResponseFrom(http_response);
    }
    catch (const BaseException& e) {
      // TODO(in.heo): Be better exception naming
      throw FailParseRetrieveRoomResponseException(e.what());
    }
    return response;
  }

  throw FailRetrieveRoomException(http_response.GetErrorMessage().c_str());
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
