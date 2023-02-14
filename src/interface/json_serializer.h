#ifndef JSON_SERIALIZER_H_
#define JSON_SERIALIZER_H_

#include <json/json.h>
#include <memory>
#include <string>

#include "common/exception/json/invalid_json_serializer_exception.h"
#include "common/exception/json/Invalid_json_string_exception.h"

class JsonSerializer {
public:
  JsonSerializer() {
    reader_builder_ = std::make_shared<Json::CharReaderBuilder>();
    reader_ = reader_builder_->newCharReader();

    writer_builder_ = std::make_shared<Json::StreamWriterBuilder>();
  }

  virtual ~JsonSerializer() {
    reader_builder_.reset();
    reader_.reset();

    writer_builder_.reset();
  }

  static Json::Value ParseJson(const std::string& json) const;
  static std::string ToSting(const Json::Value& json) const;

private:
  std::shared_ptr<Json::CharReaderBuilder> reader_builder_;
  std::shared_ptr<Json::CharReader> reader_;

  std::shared_ptr<Json::StreamWriterBuilder> writer_builder_;
};

static inline Json::Value JsonSerializer::ParseJson(const std::string& json) const {
  if (reader_ == nullptr) {
    throw InvalidJsonSerializerException("CharReader is invalid");
  }
  
  Json::Value json_object;
  std::string errors;

  bool result = reader_->parse(json.c_str(), json.c_str() + json.size(), &json_object, &errors);

  if (!result) {
    throw InvalidJsonStringException("Failed to parse json");
  }

  return json_object;
}

static inline std::string JsonSerializer::ToString(const Json::Value& json) const {
  if (writer_builder_ == nullptr) {
    throw InvalidJsonSerializerException("WriterBuilder is invalid");
  }

  std::string json_str = Json::writeString(&writer_builder_.get(), json);
  
  return json_str;
}

#endif
