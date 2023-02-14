#include "request.h"

Request::Request(const string &url) : url_(url), path_("")
{
}

Request::~Request()
{
}

void Request::SetPath(const string &path)
{
  path_ = path;
}

string Request::GetFullUrl() const
{
  return url_ + path_;
}
