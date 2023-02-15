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

  std::string GetBaseUrl()
  {
    return GetURL() + ":" + GetPort();
  }

private:
  void CheckParameterLength(std::string url)
  {
    if (url.length() < 7)
      throw InvalidParameterException("IP Address is too short");
  }

  void CheckProtocol(std::string url)
  {
    if (url.substr(0, 5) == "https")
      throw InvalidParameterException("SSL is not supported");
  }

  void CheckInvalidProtocol(std::string url)
  {
    std::size_t pos = url.find(vUrlDelimitor);
    if (pos != std::string::npos && url.substr(0, pos) != "http")
      throw InvalidParameterException(
          std::string("Supporting only http protocol. " + url.substr(0, pos) +
                      " is not being supported.")
              .c_str());
  }

  void CheckURLFormat(std::string url)
  {
    std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    if (url != "localhost" && !regex_match(url, ipv4))
      throw InvalidParameterException(std::string("Server Address is not correct : " + url).c_str());
  }

  std::string GetURL()
  {
    std::string url = vHttpProtocol + vDefaultUrl;
    if (argc_ <= 1) return url;
    {
      std::string argv = std::string(argv_[1]);
      std::size_t pos = argv.find(vUrlDelimitor);
      url = pos != std::string::npos ? argv.substr(pos + vUrlDelimitor.length()) : argv;

      try
      {
        CheckParameterLength(argv);
        CheckProtocol(argv);
        CheckInvalidProtocol(argv);
        CheckURLFormat(url);
      }
      catch (const InvalidParameterException &e)
      {
        throw InvalidParameterException(e.what());
      }
    }

    return vHttpProtocol + url;
  }

  void CheckPortLength(std::string port)
  {
    if (port.length() > 5)
      throw InvalidParameterException("The length of port is too long");
  }

  void CheckPortIsNumber(std::string port)
  {
    std::string::const_iterator it = port.begin();
    while (it != port.end() && std::isdigit(*it))
      ++it;

    if (it != port.end())
      throw InvalidParameterException("Port must be a number");
  }

  void CheckPortRange(std::string port)
  {
    if (stoi(port) > 65535 || stoi(port) <= 0)
      throw InvalidParameterException("Port is out of range");
  }

  std::string GetPort()
  {
    std::string port = vDefaultPort;

    if (argc_ <= 2)
      return port;

    port = std::string(argv_[2]);

    try
    {
      CheckPortLength(port);
      CheckPortIsNumber(port);
      CheckPortRange(port);
    }
    catch (const InvalidParameterException &e)
    {
      throw InvalidParameterException(e.what());
    }

    return port;
  }

  int argc_;
  char **argv_;
  std::string baseurl_;
  const std::string vHttpProtocol = "http://";
  const std::string vUrlDelimitor = "://";
  const std::string vDefaultUrl = "10.241.114.152";
  const std::string vDefaultPort = "34568";
};

#endif
