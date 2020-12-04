/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-10-12
 */

#pragma once

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
    std::map<std::string, epicsUInt32> getMap() const { return mapsi; };

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

  class YmlPBPresentIds : public YmlKeyValMap
  {
  public:
    YmlPBPresentIds(){};
    int init(std::string fname, std::string nodeName = "PBPresent", std::string valName = "id")
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
    uint getProtVer() { return m_ProtVer; };
    uint getProtNum() { return m_ProtNum; };
    YmlPBStateIds m_PBStateIds;
    YmlPBModIds m_PBModIds;
    YmlPBDestIds m_PBDestIds;
    YmlPBPresentIds m_PBPresentIds;

  private:
    uint m_ProtVer = 0;
    uint m_ProtNum = 0;
  };

  class YmlSCEConfig : public YmlNode
  {
  public:
    //YmlInhibitEvt(std::string fname);
    YmlSCEConfig(){};
    int init(std::string fname);
    std::vector<std::string> get_PBSwOff_Evts() const { return m_PBSwOff_Evts; };
    std::vector<std::string> get_PBSwOff_States() const { return m_PBSwOff_States; };
    std::vector<std::string> get_PBSwOff_Mods() const { return m_PBSwOff_Mods; };
    std::string SCESwitchBehaviour(bool trig = false);

    int do_PBSwOff_Evts(std::map<std::string, std::string> &cycle_row);
    int do_PBSwOff_States(std::map<std::string, std::string> &cycle_row);

  protected:
    int get_ScTSwitch_Off() { return m_ScTSwitch_Off; };

  private:
    std::vector<std::string> m_PBSwOff_Evts;
    std::vector<std::string> m_PBSwOff_States;
    std::vector<std::string> m_PBSwOff_Mods;
    int m_ScTSwitch_Off = 0;
  };

} // namespace io
