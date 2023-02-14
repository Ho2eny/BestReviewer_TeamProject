#ifndef USER_REPOSITORY_H_
#define USER_REPOSITORY_H_

#include "../dto/user/login_request.h"
#include "../dto/User/login_response.h"

class UserRepository {
public:
  virtual LoginResponse Login(const LoginRequest& request) = 0;
};

#endif
