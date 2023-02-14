#ifndef  _RESPONSE_H_ 
#define  _RESPONSE_H_ 

#include <string>

using std::string;

// TODO
class Response {
public:
  Response() {}
  Response(int status_code, const string &body);
  ~Response();

  int GetStatusCode() const { return 0; } 
  string GetBody() const { return ""; }

private:
  int status_code_;
  string body_;
};

#endif