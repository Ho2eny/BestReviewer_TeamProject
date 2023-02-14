#ifndef _HTTP_PLUGIN_H_
#define _HTTP_PLUGIN_H_

#include "request.h"
#include "response.h"

class HttpPlugin {
public:
  virtual Response Get(Request request) = 0;
  virtual Response Post(Request request) = 0;
  virtual Response Put(Request request) = 0;
  virtual Response Delete(Request request) = 0;
};

#endif