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
    std::string sessionID = cache_.GetValue(Cache::vSessionID);
    if (sessionID.empty())
      throw InvalidCommandException("Session is not exists");

    LogoutRequest request(sessionID);
    try
    {
      LogoutResponse response = repository_->Logout(request);
      cache_.RemoveSessionID();

      AnsiColor color;
      color.TextWithLineFeed("Logged out");
    }
    catch (const InternalException &ex)
    {
      throw GeneralNetworkException(ex.what());
    }
    catch (const AuthenticationFailureException &ex)
    {
      throw GeneralNetworkException(ex.what());
    }
    catch (const ConnectionFailureException &ex)
    {
      throw GeneralNetworkException(ex.what());
    }
    catch (const DnsResolvingFailureException &ex)
    {
      throw GeneralNetworkException(ex.what());
    }
    catch (const FailLogoutException &ex)
    {
      throw InvalidCommandException(ex.what());
    }
  }
};

#endif
