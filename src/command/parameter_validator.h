#ifndef PARAMETER_VALIDATOR_H_
#define PARAMETER_VALIDATOR_H_

#include <string>
#include <bits/stdc++.h>
#include "../common/exception/parameter/invalid_parameter_exception.h"

class ParameterValidator
{
public:
  ParameterValidator(int argc, char **argv)
      : argc_(argc), argv_(argv), baseurl_("http://10.241.114.152:34568") {}

  std::string GetBaseUrl();

private:
  void CheckParameterLength(std::string url);
  void CheckProtocol(std::string url);
  void CheckInvalidProtocol(std::string url);
  void CheckURLFormat(std::string url);
  std::string GetURL();
  void CheckPortLength(std::string port);
  void CheckPortIsNumber(std::string port);
  void CheckPortRange(std::string port);
  std::string GetPort();

  int argc_;
  char **argv_;
  std::string baseurl_;
  const std::string vHttpProtocol = "http://";
  const std::string vUrlDelimitor = "://";
  const std::string vDefaultUrl = "10.241.114.152";
  const std::string vDefaultPort = "34568";
};

#endif
