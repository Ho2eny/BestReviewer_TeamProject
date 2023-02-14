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

private:
  string url_;
  string path_;
};

#endif