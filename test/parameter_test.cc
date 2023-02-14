#include <gtest/gtest.h>
#include "../src/command/parameter_validator.h"

using namespace std;

TEST(ParameterTest, addressException)
{
  const char *argv1[] = {"client", "https://10.88.49.247"};
  int argc = sizeof(argv1) / sizeof(char *);
  ParameterValidator validator1(argc, const_cast<char **>(argv1));
  ASSERT_THROW(validator1.GetBaseUrl(), InvalidParameterException);

  const char *argv2[] = {"client", "ftp://10.88.49.247"};
  argc = sizeof(argv2) / sizeof(char *);
  ParameterValidator validator2(argc, const_cast<char **>(argv2));
  ASSERT_THROW(validator2.GetBaseUrl(), InvalidParameterException);

  const char *argv3[] = {"client", "http://256.88.49.247"};
  argc = sizeof(argv3) / sizeof(char *);
  ParameterValidator validator3(argc, const_cast<char **>(argv3));
  ASSERT_THROW(validator3.GetBaseUrl(), InvalidParameterException);

  const char *argv4[] = {"client", "localhosts"};
  argc = sizeof(argv4) / sizeof(char *);
  ParameterValidator validator4(argc, const_cast<char **>(argv4));
  ASSERT_THROW(validator4.GetBaseUrl(), InvalidParameterException);

  const char *argv5[] = {"client", "http://10.241.114.152"};
  argc = sizeof(argv5) / sizeof(char *);
  ParameterValidator validator5(argc, const_cast<char **>(argv5));
  ASSERT_EQ(validator5.GetBaseUrl(), "http://10.241.114.152:34568");

  const char *argv6[] = {"client", "10.241.114.152"};
  argc = sizeof(argv6) / sizeof(char *);
  ParameterValidator validator6(argc, const_cast<char **>(argv6));
  ASSERT_EQ(validator6.GetBaseUrl(), "http://10.241.114.152:34568");

  const char *argv7[] = {"client", "10.241.114.152:34568"};
  argc = sizeof(argv7) / sizeof(char *);
  ParameterValidator validator7(argc, const_cast<char **>(argv7));
  ASSERT_THROW(validator7.GetBaseUrl(), InvalidParameterException);

  const char *argv8[] = {"client", "10"};
  argc = sizeof(argv8) / sizeof(char *);
  ParameterValidator validator8(argc, const_cast<char **>(argv8));
  ASSERT_THROW(validator8.GetBaseUrl(), InvalidParameterException);
}

TEST(ParameterTest, portException)
{
  const char *argv1[] = {"client", "10.241.114.152"};
  int argc = sizeof(argv1) / sizeof(char *);
  ParameterValidator validator1(argc, const_cast<char **>(argv1));
  ASSERT_EQ(validator1.GetBaseUrl(), "http://10.241.114.152:34568");

  const char *argv2[] = {"client", "10.241.114.152", "34568"};
  argc = sizeof(argv2) / sizeof(char *);
  ParameterValidator validator2(argc, const_cast<char **>(argv2));
  ASSERT_EQ(validator2.GetBaseUrl(), "http://10.241.114.152:34568");

  const char *argv3[] = {"client", "10.241.114.152", "1234567"};
  argc = sizeof(argv3) / sizeof(char *);
  ParameterValidator validator3(argc, const_cast<char **>(argv3));
  ASSERT_THROW(validator3.GetBaseUrl(), InvalidParameterException);

  const char *argv4[] = {"client", "10.241.114.152", "65536"};
  argc = sizeof(argv4) / sizeof(char *);
  ParameterValidator validator4(argc, const_cast<char **>(argv4));
  ASSERT_THROW(validator4.GetBaseUrl(), InvalidParameterException);
}
