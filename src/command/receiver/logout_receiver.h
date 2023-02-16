#ifndef LOGOUT_RECEIVER_H_
#define LOGOUT_RECEIVER_H_

#include <iostream>
#include "../cache.h"
#include "user_receiver.h"
#include "../../common/exception/user/fail_logout_exception.h"

class LogoutReceiver : public UserReceiver
{
public:
  LogoutReceiver(Cache &cache, std::shared_ptr<UserRepository> repository) : UserReceiver(cache, repository) {}

  void Action() override
  {
    AnsiColor color;
    std::string sessionID = cache_.GetValue(Cache::vSessionID);
    if (sessionID.empty())
      throw InvalidCommandException("Session is not exists");

    try
    {
      LogoutRequest request(sessionID);
      LogoutResponse response = repository_->Logout(request);
      cache_.RemoveSessionID();
      color.TextWithLineFeed("Logged out");
    }
    catch (const FailLogoutException &ex)
    {
      throw InvalidCommandException(std::string(sessionID + " " + ex.what()).c_str());
    }
  }
};

#endif
