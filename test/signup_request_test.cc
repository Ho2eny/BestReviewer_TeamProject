#include <gtest/gtest.h>

#include "../src/interface/dto/user/signup_request.h"
#include "../src/common/exception/user/invalid_id_password_exception.h"

TEST(SignupRequestTest, exceptionWhenIdPasswordInvalid) {
  EXPECT_THROW(SignupRequest kIdHasProhibitComma("invalid,", "password"), InvalidIdPasswordException);
  EXPECT_THROW(SignupRequest kIdHasProhibitPipe("invalid|", "password"), InvalidIdPasswordException);
  EXPECT_THROW(SignupRequest kIdHasProhibitCommaAndPipe("invali,d|", "password"), InvalidIdPasswordException);
  EXPECT_THROW(SignupRequest kPasswordHasProhibitComma("invalid", "password,"), InvalidIdPasswordException);
  EXPECT_THROW(SignupRequest kIdPasswordHasProhibit("inv,alid", "pa,ssword,"), InvalidIdPasswordException);
}