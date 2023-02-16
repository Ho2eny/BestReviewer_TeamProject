#include "json_serializer.h"

#include "exception/invalid_json_serializer_exception.h"
#include "exception/invalid_json_string_exception.h"

JsonSerializer::JsonSerializer() {
  reader_builder_ = std::make_shared<Json::CharReaderBuilder>();
  writer_builder_ = std::make_shared<Json::StreamWriterBuilder>();
}

JsonSerializer::~JsonSerializer() {
  reader_builder_.reset();
  writer_builder_.reset();
}

Json::Value JsonSerializer::ParseJson(const std::string& json) const {
  if (reader_builder_ == nullptr) {
    throw InvalidJsonSerializerException("ReaderBuilder is invalid");
  }
  
  Json::CharReader* reader = reader_builder_->newCharReader();

  if (reader == nullptr) {
    throw InvalidJsonSerializerException("Failed to create CharReader with CharReaderBuilder");
  }

  Json::Value json_object;
  std::string errors;

  if (!reader->parse(json.c_str(), json.c_str() + json.size(), &json_object, &errors)) {
    throw InvalidJsonStringException("Failed to parse json");
  }

  return json_object;
}

std::string JsonSerializer::ToString(const Json::Value& json) const {
  if (writer_builder_ == nullptr) {
    throw InvalidJsonSerializerException("WriterBuilder is invalid");
  }

  std::string json_str = Json::writeString(*writer_builder_.get(), json);
  
  return json_str;
}
