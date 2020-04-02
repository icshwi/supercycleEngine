/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "json.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

#include <iostream>
#include <fstream>
#include <json/json.h>

#include <algorithm>
#include "cmnbase.hpp"

namespace io
{

void json2map(Json::Value &argjval, std::map<std::string, std::string> &argm, std::string key)
{
    std::vector<std::string> tmpv = argjval.getMemberNames();

    for (auto const &it : tmpv)
    {
        argm[it] = argjval[it].get(key, "").asString();
    }
}

void json2map(Json::Value &argjval, std::map<std::string, epicsUInt32> &argm, std::string key)
{
    std::vector<std::string> tmpv = argjval.getMemberNames();

    for (auto const &it : tmpv)
    {
        argm[it] = argjval[it].get(key, "").asUInt();
    }
}

int JsonValue::init(std::string fname)
{
    io::LOG(io::DEBUG2) << "JsonValue::init() fname" << fname;

    if (cmn::isFile(fname) == false)
        return 1;

    std::ifstream ifs = {};
    Json::Reader reader = {};
    Json::Value valj = {};
    bool status = false;

    ifs.open(fname, std::ifstream::in);
    status = reader.parse(ifs, valj);
    ifs.close();

    if (status == true)
    {
        filename = fname;
        value = valj;
        keys = value.getMemberNames();
    }
    return 0;
}

int JsonDBUF::init(std::string fname)
{
    if (JsonValue::init(fname) != 0)
        return 1;

    PBDest = value[env::DBFIDX2Str.at(env::PBDest)];
    PBMod = value[env::DBFIDX2Str.at(env::PBMod)];
    PBState = value[env::DBFIDX2Str.at(env::PBState)];

    io::LOG(io::DEBUG2) << "JsonDBUF::init() fname " << fname;

    ProtVer = value[env::DBFIDX2Str.at(env::ProtVer)].asUInt();
    ProtNum = value[env::DBFIDX2Str.at(env::ProtNum)].asUInt();

    json2map(PBDest, PBDestId);
    json2map(PBMod, PBModId);
    json2map(PBState, PBStateId);

    io::LOG(io::INFO) << "JsonDBUF::init() cmn::map2str<std::string,uint>(PBDestId) " << cmn::map2str<std::string, uint>(PBDestId);
    io::LOG(io::INFO) << "JsonDBUF::init() cmn::map2str<std::string,uint>(PBModId) " << cmn::map2str<std::string, uint>(PBModId);
    io::LOG(io::INFO) << "JsonDBUF::init() cmn::map2str<std::string,uint>(PBStateId) " << cmn::map2str<std::string, uint>(PBStateId);

    return 0;
}

int JsonEVT::init(std::string fname)
{
    if (JsonValue::init(fname) != 0)
        return 1;

    io::LOG(io::DEBUG2) << "JsonEVT::init() fname " << fname;
    json2map(value, evtm);
    io::LOG(io::INFO) << "JsonEVT::init() cmn::map2str<std::string,uint>(evtm) " << cmn::map2str<std::string, uint>(evtm);

    return 0;
}

} // namespace io
