#ifndef CMDREADJSON_HPP_
#define CMDREADJSON_HPP_

#include <jsoncpp/json/json.h>
#include <vector>
#include <string>

class JsonRoot
{
protected:
    std::vector<std::string> fnamev;
    std::vector<Json::Value> rootv;
    std::vector<std::vector<std::string>> keyv;

public:
    JsonRoot(){};
    virtual void init(std::string fname);
};

JsonRoot &RegisteredJsonRoot();
extern std::vector<std::string> RegisteredStringV;

#endif // CMDREADJSON_HPP_
