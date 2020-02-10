#ifndef JSON_HPP
#define JSON_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <map>
#include "scenv.hpp"

namespace io
{

class JsonValue
{
protected:
    std::string filename;
    Json::Value value;
    std::vector<std::string> keys;
public:
    JsonValue(std::string fname);
    //JSONValue(){};
    virtual void init(std::string fname);
};

class JsonDBUF : public JsonValue
{
public:
    JsonDBUF(std::string fname);
    // JSONESS(){};
    //void init(std::string fname);
    uint ProtVer;
    uint ProtNum;
    Json::Value& PBDest;
    Json::Value& PBMod;
    Json::Value& PBState;
    uint getPBDestId    (std::string key){return PBDestId[key];};
    uint getPBModId     (std::string key){return PBModId[key];};
    uint getPBStateId   (std::string key){return PBStateId[key];};
private:
    std::map<std::string,uint> PBDestId;
    std::map<std::string,uint> PBModId;
    std::map<std::string,uint> PBStateId;
};

class JsonEVT : public JsonValue
{
public:
    JsonEVT(std::string fname);
    uint getEvtCode(std::string key){return evtm[key];};
    std::map<std::string,uint> getEvtMap(){return evtm;};
private:
    std::map<std::string,uint> evtm;
};

} //namespace

// Test Space
/*
void json_test(std::string file_path="../reftabs/init/databuffer-ess.json");
void json_test1(std::string file_path="../reftabs/init/databuffer-ess.json");
void json_test2(std::string file_path="../reftabs/init/databuffer-ess.json");
*/

#endif // JSON_HPP
