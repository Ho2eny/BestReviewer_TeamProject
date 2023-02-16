#include "response.h"

Response::Response() : status_code_(0), body_("")
{

}

Response::Response(int status_code, const string &body)
    : status_code_(status_code), body_(body)
{
}

Response::~Response()
{
}


int Response::GetStatusCode() const
{
  return status_code_;
} 

string Response::GetBody() const
{
  return body_;
}

bool Response::IsSuccess() const
{
  return (status_code_ < kHttpRedirectionCode
    && status_code_ >= kHttpSuccessCode);
}
