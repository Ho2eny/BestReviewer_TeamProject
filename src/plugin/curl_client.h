#ifndef _CURL_CLIENT_H_
#define _CURL_CLIENT_H_

#include <curl/curl.h>

#include "../http_plugin.h"
#include "../request.h"
#include "../response.h"


class CurlClient : public HttpPlugin {
public:
  CurlClient();
  ~CurlClient();

  virtual Response Get(Request request) override;
  virtual Response Post(Request request) override;
  virtual Response Put(Request request) override;
  virtual Response Delete(Request request) override;

private:
  void Initialize();
  void Deinitialize();

  void SetUp(const Request &request);
  void CleanUp();

  void AppendHeader(const string &key, const string &value);
  string GetErrorMessage(int result);
  void HandleResultCode(int code);
  
  static size_t WriteBodyCallback(void *contents,
      size_t size, size_t nmemb, void *userp);

  CURL *curl_;
  struct curl_slist *header_;
  string body_;
};

#endif