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

  int GetStatusCode() const { return status_code_; } 
  string GetErrorMessage() const { return error_message_; }
  string GetBody() const { return body_; }

private:
  int status_code_;
  string error_message_;
  string body_;
};

#endif