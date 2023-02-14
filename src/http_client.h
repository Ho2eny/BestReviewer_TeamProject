#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_

#include <memory>

#include "http_plugin.h"
#include "request.h"
#include "response.h"

#include "plugin/curl_client.h"

// TODO
class HttpClient {
public:
  HttpClient();
  ~HttpClient();

  Response Get(Request request);
  Response Post(Request request);
  Response Put(Request request);
  Response Delete(Request request);

private:
  std::shared_ptr<HttpPlugin> plugin;
};

HttpClient::HttpClient()
{
  plugin = std::make_shared<CurlClient>();
}

#endif