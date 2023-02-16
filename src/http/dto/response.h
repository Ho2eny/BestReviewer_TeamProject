#ifndef  _RESPONSE_H_ 
#define  _RESPONSE_H_ 

#include <string>

using std::string;

class Response {
public:
  Response() : status_code_(0), error_message_(""), body_("") {}
  Response(int status_code, const string &error_message, const string &body)
    : status_code_(status_code), error_message_(error_message), body_(body) {}
  ~Response() {}

  Response& operator=(const Response &response) {
    status_code_ = response.GetStatusCode();
    error_message_ = response.GetErrorMessage();
    body_ = response.GetBody();
    return *this;
  }

  int GetStatusCode() const { return status_code_; } 
  string GetErrorMessage() const { return error_message_; }
  string GetBody() const { return body_; }
  bool IsSuccess() const { return (status_code_ < kHttpRedirectionCode && status_code_ >= kHttpSuccessCode); }

private:
  int status_code_;
  string error_message_;
  string body_;
  
  const int kHttpSuccessCode = 200;
  const int kHttpRedirectionCode = 300;
};

#endif