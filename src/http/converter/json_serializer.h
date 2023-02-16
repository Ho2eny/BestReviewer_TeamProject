#ifndef JSON_SERIALIZER_H_
#define JSON_SERIALIZER_H_

#include <json/json.h>
#include <memory>
#include <string>

class JsonSerializer {
public:
  JsonSerializer();
  virtual ~JsonSerializer();

  Json::Value ParseJson(const std::string& json) const;
  std::string ToString(const Json::Value& json) const;

protected:
  std::shared_ptr<Json::CharReaderBuilder> reader_builder_;
  std::shared_ptr<Json::StreamWriterBuilder> writer_builder_;
};

#endif
