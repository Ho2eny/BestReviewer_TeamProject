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
    return GetAddress() + ":" + GetPort();
  }

private:
  std::string GetAddress()
  {
    std::string host = "10.241.114.152";
    if (argc_ > 1)
    {
      std::string argv = std::string(argv_[1]);
      if (argv.length() < 7)
        throw InvalidParameterException("IP Address is too short");

      if (argv.substr(0, 5) == "https")
        throw InvalidParameterException("SSL is not supported");

      std::size_t pos = argv.find("://");
      if (pos != std::string::npos && argv.substr(0, pos) != "http")
        throw InvalidParameterException(std::string("Supporting only http protocol. " + argv.substr(0, pos) + " is not being supported.").c_str());

      host = pos != std::string::npos ? argv.substr(pos + 3) : argv;
      std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
      if (host != "localhost" && !regex_match(host, ipv4))
        throw InvalidParameterException(std::string("Server Address is not correct : " + host).c_str());
    }

    return "http://" + host;
  }

  std::string GetPort()
  {
    std::string port = "34568";

    if (argc_ > 2)
    {
      port = std::string(argv_[2]);

      if (port.length() > 5)
        throw InvalidParameterException("The length of port is too long");

      std::string::const_iterator it = port.begin();
      while (it != port.end() && std::isdigit(*it))
        ++it;

      if (it != port.end())
        throw InvalidParameterException("Port must be a number");

      if (stoi(port) > 65535 || stoi(port) <= 0)
        throw InvalidParameterException("Out of range");
    }

    return port;
  }

  int argc_;
  char **argv_;
  std::string baseurl_;
};

#endif
