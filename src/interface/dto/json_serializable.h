#ifndef JSON_SERIALIZABLE_H_
#define JSON_SERIALIZABLE_H_

class JsonSerializable {
public:
  JsonSerializable() {}

  virtual void ParseJson(const std::string& json) = 0;

  virtual std::string ToJson() = 0;
};

#endif
