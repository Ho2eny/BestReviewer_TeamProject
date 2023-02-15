#ifndef  _REQUEST_H_ 
#define  _REQUEST_H_ 

#include <string>

using std::string;

class Request {
public:
  Request(const string &url);
  ~Request();

  void SetPath(const string &path);
  string GetFullUrl() const;

  void SetBody(const string &body);
  string GetBody() const;

private:
  string url_;
  string path_;
  string body_;
};

#endif