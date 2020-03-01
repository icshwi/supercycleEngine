#ifndef JSON_HPP_
#define JSON_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <map>
#include "scenv.hpp"

#include <epicsTypes.h>

namespace io
{

void json2map(Json::Value &, std::map<std::string, std::string> &, std::string key = "id");
void json2map(Json::Value &, std::map<std::string, epicsUInt32> &, std::string key = "id");

class JsonValue
{
protected:
    std::string filename;
    Json::Value value;
    std::vector<std::string> keys;

public:
    //JsonValue(std::string fname);
    JsonValue(){};
    virtual int init(std::string fname);
};

class JsonDBUF : public JsonValue
{
public:
    //JsonDBUF(std::string fname);
    JsonDBUF(){};
    int init(std::string fname);

    Json::Value PBDest;
    Json::Value PBMod;
    Json::Value PBState;
    uint getPBDestId(std::string key) { return PBDestId[key]; };
    uint getPBModId(std::string key) { return PBModId[key]; };
    uint getPBStateId(std::string key) { return PBStateId[key]; };
    uint getProtVer() { return ProtVer; };
    uint getProtNum() { return ProtNum; };

private:
    std::map<std::string, uint> PBDestId;
    std::map<std::string, uint> PBModId;
    std::map<std::string, uint> PBStateId;
    uint ProtVer;
    uint ProtNum;
};

class JsonEVT : public JsonValue
{
public:
    //JsonEVT(std::string fname);
    JsonEVT(){};
    int init(std::string fname);
    uint getEvtCode(std::string key) { return evtm[key]; };
    std::map<std::string, uint> getEvtMap() { return evtm; };

private:
    std::map<std::string, uint> evtm;
};

} // namespace io

#endif // JSON_HPP
