#ifndef LOGIN_RECEIVER_H_
#define LOGIN_RECEIVER_H_

#include <iostream>
#include <memory>
#include "../cache.h"
#include "../../utils.h"
#include "user_receiver.h"
#include "../../common/exception/user/fail_login_exception.h"

class LoginReceiver : public UserReceiver
{
public:
  LoginReceiver(Cache &cache, std::shared_ptr<UserRepository> repository) : UserReceiver(cache, repository) {}

  void Action() override
  {
    AnsiColor color;

    std::string id = GetId();
    std::string password = GetPassword();
    AuthorizationKey key(id, password);

    try
    {
      LoginRequest request(id, key.QueryNonce(), key.QueryPasswordWithNonce());
      LoginResponse response = repository_->Login(request);
      cache_.SetSessionID(response.GetSessionId());

      color.TextWithLineFeed("Logged in with " + id);
    }
    catch (const FailLoginException &ex)
    {
      throw InvalidCommandException(std::string(id + " " + ex.what()).c_str());
    }
  }
};

#endif
