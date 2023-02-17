#ifndef  _RESPONSE_H_ 
#define  _RESPONSE_H_ 

#include <string>

using std::string;

class Response {
public:
  Response();
  Response(int status_code, const string &body);
  ~Response();

  int GetStatusCode() const;
  string GetBody() const;
  bool IsSuccess() const;

  
  Response& operator=(const Response &response) {
    status_code_ = response.GetStatusCode();
    body_ = response.GetBody();
    return *this;
  }

private:
  int status_code_;
  string body_;
  
  const int kHttpSuccessCode = 200;
  const int kHttpRedirectionCode = 300;
};

#endif