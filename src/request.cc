#include "request.h"

Request::Request(const string &url) : url_(url), path_(""), body_("")
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

void Request::SetBody(const string &body)
{
  body_ = body;
}

string Request::GetBody() const
{
  return body_;
}