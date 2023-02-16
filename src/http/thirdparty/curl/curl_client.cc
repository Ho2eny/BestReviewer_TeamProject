#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include "curl_client.h"
#include "../../exception/network/connection_failure_exception.h"
#include "../../exception/network/dns_resolving_failure_exception.h"
#include "../../exception/network/internal_exception.h"

using namespace std;

bool CurlClient::isGlobalInit_ = false;

CurlClient::CurlClient() : curl_(nullptr), header_(nullptr), body_("")
{
  Initialize();
}

CurlClient::~CurlClient()
{
  Deinitialize();
}

void CurlClient::Initialize()
{
    if (isGlobalInit_) return;

    curl_global_init(CURL_GLOBAL_ALL);
    isGlobalInit_ = true;
}

void CurlClient::Deinitialize()
{
  if (!isGlobalInit_) return;

  curl_global_cleanup();
  isGlobalInit_ = false;
}

Response CurlClient::Get(Request request)
{
  mutex_.lock();
  SetUp(request);

  curl_easy_setopt(curl_, CURLOPT_HTTPGET, 1L);
  CURLcode res = curl_easy_perform(curl_);
  HandleResultCode(res);
  
  int status_code = 0;
  curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &status_code);
  auto response = Response(status_code, body_);

  CleanUp();
  mutex_.unlock();

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
  if (header_)
    curl_slist_free_all(header_);

  curl_ = nullptr;
  header_ = nullptr;
  body_ = "";
}

Response CurlClient::Post(Request request)
{
  mutex_.lock();
  SetUp(request);

  AppendHeader("Content-Type", "application/json");

  curl_easy_setopt(curl_, CURLOPT_POST, 1L);
  curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, request.GetBody().c_str());
  
  CURLcode res = curl_easy_perform(curl_);
  HandleResultCode(res);
  
  int status_code = 0;
  curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &status_code);
  auto response = Response(status_code, body_);

  CleanUp();
  mutex_.unlock();

  return response;
}

Response CurlClient::Put(Request request)
{
  return Response();
}

Response CurlClient::Delete(Request request)
{  
  mutex_.lock();
  SetUp(request);

  curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "DELETE");
  CURLcode result = curl_easy_perform(curl_);
  HandleResultCode(result);
  int status_code = 0;

  curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &status_code);
  auto response = Response(status_code, body_);

  CleanUp();
  mutex_.unlock();

  return response;
}

void CurlClient::AppendHeader(const string &key, const string &value)
{
  stringstream ss;

  ss << key << ": " << value;
  
  header_ = curl_slist_append(header_, ss.str().c_str());  
  if (!header_)
    throw InternalException("header list cannot be NULL.");

  curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, header_);
}

void CurlClient::HandleResultCode(int code)
{
  switch (code) {
    case CURLE_OK:
      return;
    case CURLE_COULDNT_RESOLVE_PROXY:
    case CURLE_COULDNT_RESOLVE_HOST:
      mutex_.unlock();
      throw DnsResolvingFailureException("DNS resolving failed.");
    case CURLE_COULDNT_CONNECT:
      mutex_.unlock();
      throw ConnectionFailureException("TCP connection failed.");
    default:
      mutex_.unlock();
      throw InternalException("Error occured in libcurl internally.");
  }
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