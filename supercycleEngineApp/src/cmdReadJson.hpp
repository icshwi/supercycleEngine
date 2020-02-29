#ifndef CMDREADJSON_HPP_
#define CMDREADJSON_HPP_

#include <jsoncpp/json/json.h>
#include <vector>
#include <string>

class JsonRootV
{
protected:
    std::vector<std::string> fnamev;
    std::vector<Json::Value> rootv;
    std::vector<std::vector<std::string>> keyv;

public:
    JsonRootV(){};
    virtual void init(std::string fname);
};

JsonRootV &RegisteredJsonRoot();

#endif // CMDREADJSON_HPP_
