#ifndef  _RESPONSE_H_ 
#define  _RESPONSE_H_ 

#include <string>

using std::string;

class Response {
public:
  Response() : status_code_(0), body_("") {}
  Response(int status_code, const string &body)
    : status_code_(status_code), body_(body) {}
  ~Response() {}

  int GetStatusCode() const { return status_code_; } 
  string GetBody() const { return body_; }

private:
  int status_code_;
  string body_;
};

#endif