#include <gtest/gtest.h>
#include "../src/command/parameter_validator.h"

using namespace std;

TEST(ParameterTest, addressException)
{
  const char *https_not_support[] = {"client", "https://10.88.49.247"};
  int argc = sizeof(https_not_support) / sizeof(char *);
  ParameterValidator validator1(argc, const_cast<char **>(https_not_support));
  ASSERT_THROW(validator1.GetBaseUrl(), InvalidParameterException);

  const char *ftp_not_support[] = {"client", "ftp://10.88.49.247"};
  argc = sizeof(ftp_not_support) / sizeof(char *);
  ParameterValidator validator2(argc, const_cast<char **>(ftp_not_support));
  ASSERT_THROW(validator2.GetBaseUrl(), InvalidParameterException);

  const char *range_out[] = {"client", "http://256.88.49.247"};
  argc = sizeof(range_out) / sizeof(char *);
  ParameterValidator validator3(argc, const_cast<char **>(range_out));
  ASSERT_THROW(validator3.GetBaseUrl(), InvalidParameterException);

  const char *typo_error[] = {"client", "localhosts"};
  argc = sizeof(typo_error) / sizeof(char *);
  ParameterValidator validator4(argc, const_cast<char **>(typo_error));
  ASSERT_THROW(validator4.GetBaseUrl(), InvalidParameterException);

  const char *correct_test[] = {"client", "http://10.241.114.152"};
  argc = sizeof(correct_test) / sizeof(char *);
  ParameterValidator validator5(argc, const_cast<char **>(correct_test));
  ASSERT_EQ(validator5.GetBaseUrl(), "http://10.241.114.152:34568");

  const char *correct_test_wo_protocol[] = {"client", "10.241.114.152"};
  argc = sizeof(correct_test_wo_protocol) / sizeof(char *);
  ParameterValidator validator6(argc, const_cast<char **>(correct_test_wo_protocol));
  ASSERT_EQ(validator6.GetBaseUrl(), "http://10.241.114.152:34568");

  const char *port_in_url[] = {"client", "10.241.114.152:34568"};
  argc = sizeof(port_in_url) / sizeof(char *);
  ParameterValidator validator7(argc, const_cast<char **>(port_in_url));
  ASSERT_THROW(validator7.GetBaseUrl(), InvalidParameterException);

  const char *wrong_ip[] = {"client", "10"};
  argc = sizeof(wrong_ip) / sizeof(char *);
  ParameterValidator validator8(argc, const_cast<char **>(wrong_ip));
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

  const char *argv5[] = {"client", "10.241.114.152", "abc"};
  argc = sizeof(argv5) / sizeof(char *);
  ParameterValidator validator5(argc, const_cast<char **>(argv5));
  ASSERT_THROW(validator5.GetBaseUrl(), InvalidParameterException);
}
