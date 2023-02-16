#ifndef LOGIN_RECEIVER_H_
#define LOGIN_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "../../utils.h"
#include "user_receiver.h"

class LoginReceiver : public UserReceiver
{
public:
  LoginReceiver(Cache &cache, std::shared_ptr<UserRepository> repository) : UserReceiver(cache, repository) {}

  void Action() override
  {
    std::string id = GetId();
    std::string password = GetPassword();
    AuthorizationKey key(id, password);

    LoginRequest request(id, key.QueryNonce(), key.QueryPasswordWithNonce());
    LoginResponse response = repository_->Login(request);
    cache_.SetSessionID(response.GetSessionId());

    AnsiColor color;
    color.TextWithLineFeed("Logged in with " + id);
  }
};

#endif
