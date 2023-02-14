#ifndef  _REQUEST_H_ 
#define  _REQUEST_H_ 

#include <string>

using std::string;

// TODO
class Request {
public:
  Request(const string &url);
  ~Request();

  void SetPath(const string &path);
  string GetFullUrl() const;

private:
  string url;
  string path;
};

#endif