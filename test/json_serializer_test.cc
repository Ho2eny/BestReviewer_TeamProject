#include <gtest/gtest.h>

#include <memory>

#include "../src/http/converter/json_serializer.h"

class MockJsonSerializer : public JsonSerializer {
public:
  MockJsonSerializer() : JsonSerializer() {}

  void MakeInvalid() {
    reader_builder_ = nullptr;
    writer_builder_ = nullptr;
  }
};

class JsonSerializerTestFixture : public ::testing::Test {
protected:
  virtual void SetUp() override {
    json_serializer_ = std::make_shared<MockJsonSerializer>();
  }

  virtual void TearDown() override {
    json_serializer_.reset();
  }

  std::shared_ptr<MockJsonSerializer> json_serializer_;
};

TEST_F(JsonSerializerTestFixture, parseJsonSuccess) {
  const std::string test_welcome_json_str = "{\"message\":\"Welcome to Best Reviewer\"}";

  Json::Value json_object = json_serializer_->ParseJson(test_welcome_json_str);

  EXPECT_TRUE(json_object["message"] == "Welcome to Best Reviewer");
}

TEST_F(JsonSerializerTestFixture, parseJsonFailInvalidJsonString) {
  const std::string test_welcome_json_str = "{\"message\":\"Welcome to Best Reviewer}";

  EXPECT_THROW(json_serializer_->ParseJson(test_welcome_json_str), InvalidJsonStringException);
}

TEST_F(JsonSerializerTestFixture, parseJsonFailInvalidJsonSerializer) {
  const std::string test_welcome_json_str = "{\"message\":\"Welcome to Best Reviewer}";

  json_serializer_->MakeInvalid();
  EXPECT_THROW(json_serializer_->ParseJson(test_welcome_json_str), InvalidJsonSerializerException);
}

TEST_F(JsonSerializerTestFixture, convertToStringSuccess) {
  Json::Value json_object;
  json_object["message"] = "Easy to compose JSON string";

  std::string json_str = json_serializer_->ToString(json_object);

  const std::string expected_str = "{\n\t\"message\" : \"Easy to compose JSON string\"\n}";
  EXPECT_TRUE(json_str == expected_str);
}

TEST_F(JsonSerializerTestFixture, convertToStringFailInvalidJsonSerializer) {
  const std::string test_welcome_json_str = "{\"message\":\"Welcome to Best Reviewer}";

  json_serializer_->MakeInvalid();
  EXPECT_THROW(json_serializer_->ParseJson(test_welcome_json_str), InvalidJsonSerializerException);
}
