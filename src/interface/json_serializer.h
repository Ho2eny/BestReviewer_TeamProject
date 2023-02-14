#ifndef JSON_SERIALIZER_H_
#define JSON_SERIALIZER_H_

#include <json/json.h>
#include <memory>
#include <string>

#include "../common/exception/json/invalid_json_serializer_exception.h"
#include "../common/exception/json/Invalid_json_string_exception.h"

class JsonSerializer {
public:
  JsonSerializer() {
    reader_builder_ = std::make_shared<Json::CharReaderBuilder>();
    writer_builder_ = std::make_shared<Json::StreamWriterBuilder>();
  }

  virtual ~JsonSerializer() {
    reader_builder_.reset();
    writer_builder_.reset();
  }

  Json::Value ParseJson(const std::string& json) const;
  std::string ToString(const Json::Value& json) const;

protected:
  std::shared_ptr<Json::CharReaderBuilder> reader_builder_;
  std::shared_ptr<Json::StreamWriterBuilder> writer_builder_;
};

inline Json::Value JsonSerializer::ParseJson(const std::string& json) const {
  if (reader_builder_ == nullptr) {
    throw InvalidJsonSerializerException("ReaderBuilder is invalid");
  }
  
  Json::CharReader* reader = reader_builder_->newCharReader();

  if (reader == nullptr) {
    throw InvalidJsonSerializerException("Failed to create CharReader with CharReaderBuilder");
  }

  Json::Value json_object;
  std::string errors;

  bool result = reader->parse(json.c_str(), json.c_str() + json.size(), &json_object, &errors);

  if (!result) {
    throw InvalidJsonStringException("Failed to parse json");
  }

  return json_object;
}

inline std::string JsonSerializer::ToString(const Json::Value& json) const {
  if (writer_builder_ == nullptr) {
    throw InvalidJsonSerializerException("WriterBuilder is invalid");
  }

  std::string json_str = Json::writeString(*writer_builder_.get(), json);
  
  return json_str;
}

#endif
