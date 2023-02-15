#ifndef LOGIN_RECEIVER_H_
#define LOGIN_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "receiver.h"
#include "../../interface/dto/user/login_request.h"
#include "../../interface/dto/user/login_response.h"
// #include "../../interface/repository/user_repository.h"
#include "../../utils.h"
#include "../../ui_helper/ansi_color.h"

class LoginReceiver : public Receiver
{
public:
  LoginReceiver(Cache &cache) : Receiver(cache) {}

  void Action() override
  {
    std::string id = GetID();
    std::string password = GetPassword();
    AuthorizationKey key(id, password);
    LoginRequest request(id, key.QueryNonce(), key.QueryPasswordWithNonce());
    // UserHttpRepository repository(cache.GetValue(Cache::vBaseUrl));
    // LoginResponse response = repository.Login(request);

    cache_.SetID(id);
    // cache_.SetSessionID(response.GetSessionId());
  }

  std::string GetID()
  {
    if (cache_.GetValue(Cache::vTestID).length() > 0)
      return cache_.GetValue(Cache::vTestID);

    AnsiColor color;
    std::string id;
    color.Important("> Enter ID : ");
    std::cin >> id;
    return id;
  }

  std::string GetPassword()
  {
    if (cache_.GetValue(Cache::vTestPassword).length() > 0)
      return cache_.GetValue(Cache::vTestPassword);

    AnsiColor color;
    std::string password;
    color.Important("> Enter Password: ");
    std::cin >> password;
    return password;
  }
};

#endif
