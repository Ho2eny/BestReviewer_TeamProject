#include "http_client.h"
#include "request.h"
#include "response.h"

#include "plugin/curl_client.h"

HttpClient::HttpClient()
{
  plugin = std::make_shared<CurlClient>();
}

HttpClient::~HttpClient()
{
  plugin = std::make_shared<CurlClient>();
}

Response HttpClient::Get(Request request)
{
  return plugin->Get(request);
}

Response HttpClient::Post(Request request)
{
   return plugin->Post(request);
}

Response HttpClient::Put(Request request)
{
  return plugin->Put(request);
}

Response HttpClient::Delete(Request request)
{
  return plugin->Delete(request);
}
