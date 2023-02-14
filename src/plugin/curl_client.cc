#include <curl/curl.h>

#include "curl_client.h"
#include "../http_plugin.h"
#include "../request.h"
#include "../response.h"

using namespace std;

CurlClient::CurlClient() : curl_(nullptr), body_("")
{
  Initialize();
}

CurlClient::~CurlClient()
{
  Deinitialize();
}

void CurlClient::Initialize()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

void CurlClient::Deinitialize()
{
  curl_global_cleanup();
}

Response CurlClient::Get(Request request)
{
  SetUp(request);

  curl_easy_setopt(curl_, CURLOPT_HTTPGET, 1L);
  CURLcode res = curl_easy_perform(curl_);
  
  int status_code = 0;
  curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &status_code);
  auto response = Response(status_code, GetErrorMessage(res), body_);

  CleanUp();

  return response;
}

void CurlClient::SetUp(const Request &request)
{
  curl_ = curl_easy_init();
  curl_easy_setopt(curl_, CURLOPT_URL, request.GetFullUrl().c_str());
  curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteBodyCallback);
  curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &body_);
}

void CurlClient::CleanUp()
{
  curl_easy_cleanup(curl_);
  curl_ = nullptr;
  body_ = "";
}

string CurlClient::GetErrorMessage(int result)
{
  if (result == CURLE_OK)
    return "";

  return string("error response : ").append(to_string(result));
}

Response CurlClient::Post(Request request)
{
  return Response();
}

Response CurlClient::Put(Request request)
{
  return Response();
}

Response CurlClient::Delete(Request request)
{
  return Response();
}

size_t CurlClient::WriteBodyCallback(void *contents,
    size_t size, size_t nmemb, void *userp)
{
	char* str = static_cast<char*>(contents);
	size_t realsize = size * nmemb;
	string& res = *(static_cast<std::string*>(userp));
	res.append(str, realsize);
	return realsize;
}