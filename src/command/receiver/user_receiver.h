#ifndef USER_RECEIVER_H_
#define USER_RECEIVER_H_

#include <string>
#include "receiver.h"
#include "../../ui_helper/ansi_color.h"
#include "../../interface/repository/user_repository.h"
#include "../../interface/dto/user/login_request.h"
#include "../../interface/dto/user/login_response.h"
#include "../../interface/dto/user/logout_request.h"
#include "../../interface/dto/user/logout_response.h"
#include "../../interface/dto/user/signup_request.h"
#include "../../interface/dto/user/signup_response.h"

#include "../../http/exception/network/authentication_failure_exception.h"
#include "../../http/exception/network/connection_failure_exception.h"
#include "../../http/exception/network/dns_resolving_failure_exception.h"
#include "../../http/exception/network/internal_exception.h"
#include "../../http/exception/network/general_network_exception.h"

class UserReceiver : public Receiver
{
public:
  UserReceiver(Cache &cache, std::shared_ptr<UserRepository> repository) : Receiver(cache), repository_(repository) {}

protected:
  std::string GetId()
  {
    if (!cache_.GetValue(Cache::vTestID).empty())
      return cache_.GetValue(Cache::vTestID);

    AnsiColor color;
    std::string id;
    color.Important("> Enter ID : ");
    std::cin >> id;
    return id;
  }

  std::string GetPassword()
  {
    if (!cache_.GetValue(Cache::vTestPassword).empty())
      return cache_.GetValue(Cache::vTestPassword);

    AnsiColor color;
    std::string password;
    color.Important("> Enter Password: ");
    std::cin >> password;
    return password;
  }

  std::shared_ptr<UserRepository> repository_;
};

#endif
