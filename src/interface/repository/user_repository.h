#ifndef USER_REPOSITORY_H_
#define USER_REPOSITORY_H_

#include "../dto/user/login_request.h"
#include "../dto/user/login_response.h"
#include "../dto/user/logout_request.h"
#include "../dto/user/logout_response.h"
#include "../dto/user/signup_request.h"
#include "../dto/user/signup_response.h"

class UserRepository {
public:
  virtual LoginResponse Login(const LoginRequest& request) = 0;

  virtual SignupResponse Signup(const SignupRequest& request) = 0;

  virtual LogoutResponse Logout(const LogoutRequest& request) = 0;
};

#endif
