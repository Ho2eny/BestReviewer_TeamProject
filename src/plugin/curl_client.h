#ifndef _CURL_CLIENT_H_
#define _CURL_CLIENT_H_

#include "../http_plugin.h"
#include "../request.h"
#include "../response.h"

// TODO
class CurlClient : public HttpPlugin {
public:
  virtual Response Get(Request request) override { return Response(); }
  virtual Response Post(Request request) override { return Response(); }
  virtual Response Put(Request request) override { return Response(); }
  virtual Response Delete(Request request) override { return Response(); }
};

#endif