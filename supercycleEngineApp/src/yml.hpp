/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-10-12
 */

#ifndef YML_HPP_
#define YML_HPP_

#include "scenv.hpp"

#include <epicsTypes.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <map>

//https://github.com/jbeder/yaml-cpp/wiki/Tutorial

namespace io
{

  class YmlNode
  {
  protected:
    std::string filename;
    YAML::Node node;
    std::vector<std::string> memberNames;

  public:
    YmlNode(std::string fname);
    YmlNode(){};
    virtual int init(std::string fname);
    virtual int init(std::string fname, std::string nodeName);
    void Yml2Map(std::map<std::string, std::string> &argm, std::string key);
    void Yml2Map(std::map<std::string, epicsUInt32> &argm, std::string key);
  };

  class YmlKeyValMap : public YmlNode
  {
  public:
    //YmlIdMap(std::string fname);
    YmlKeyValMap(){};
    virtual int init(std::string fname, std::string valName);
    virtual int init(std::string fname, std::string nodeName, std::string valName);
    epicsUInt32 getVal(std::string key) { return mapsi[key]; };
    std::map<std::string, epicsUInt32> getMap() { return mapsi; };

  private:
    std::map<std::string, epicsUInt32> mapsi;
  };

  class YmlMEvts : public YmlKeyValMap
  {
  public:
    //JsonEVT(std::string fname);
    YmlMEvts(){};
    int init(std::string fname, std::string valName = "id")
    {
      YmlKeyValMap::init(fname, valName);
      return 0;
    };
  };

  class YmlPBStateIds : public YmlKeyValMap
  {
  public:
    YmlPBStateIds(){};
    int init(std::string fname, std::string nodeName = "PBState", std::string valName = "id")
    {
      YmlKeyValMap::init(fname, nodeName, valName);
      return 0;
    };
  };

  class YmlPBModIds : public YmlKeyValMap
  {
  public:
    YmlPBModIds(){};
    int init(std::string fname, std::string nodeName = "PBMod", std::string valName = "id")
    {
      YmlKeyValMap::init(fname, nodeName, valName);
      return 0;
    };
  };

  class YmlPBDestIds : public YmlKeyValMap
  {
  public:
    YmlPBDestIds(){};
    int init(std::string fname, std::string nodeName = "PBDest", std::string valName = "id")
    {
      YmlKeyValMap::init(fname, nodeName, valName);
      return 0;
    };
  };

  class YmlDatabuffer
  {
  public:
    YmlDatabuffer(){};
    int init(std::string fname);
    YmlPBStateIds PBStateIds_yml;
    YmlPBModIds PBModIds_yml;
    YmlPBDestIds PBDestIds_yml;
    uint getProtVer() { return ProtVer; };
    uint getProtNum() { return ProtNum; };

  private:
    uint ProtVer = 0;
    uint ProtNum = 0;
  };

  class YmlSCEConfig : public YmlNode
  {
  public:
    //YmlInhibitEvt(std::string fname);
    YmlSCEConfig(){};
    int init(std::string fname);
    std::vector<std::string> getInhEvts() { return inhEvtv; };
    std::vector<std::string> getInhStates() { return inhStatev; };

  private:
    std::vector<std::string> inhEvtv;
    std::vector<std::string> inhStatev;
  };

} // namespace io

#endif // YML_HPP_
