/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-10-12
 */

#pragma once

#include "scenv.hpp"

#include <epicsTypes.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

//https://github.com/jbeder/yaml-cpp/wiki/Tutorial

namespace io
{

class YmlNode
{
protected:
  std::string _filename;
  YAML::Node _node;
  std::vector<std::string> _memberNames;

public:
  explicit YmlNode(std::string fname);
  YmlNode(){};
  virtual int init(std::string fname);
  virtual int init(std::string fname, std::string nodeName);
  void Yml2Map(std::map<std::string, std::string>& argm, std::string key);
  void Yml2Map(std::map<std::string, epicsUInt32>& argm, std::string key);
};

class YmlKeyValMap : public YmlNode
{
public:
  //YmlIdMap(std::string fname);
  YmlKeyValMap(){};
  virtual int init(std::string fname, std::string valName) override;
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
  uint getProtVer() { return _ProtVer; };
  uint getProtNum() { return _ProtNum; };
  YmlPBStateIds _PBStateIds;
  YmlPBModIds _PBModIds;
  YmlPBDestIds _PBDestIds;
  YmlPBPresentIds _PBPresentIds;

private:
  uint _ProtVer = 0;
  uint _ProtNum = 0;
};

class YmlSCEConfig : public YmlNode
{
public:
  //YmlInhibitEvt(std::string fname);
  YmlSCEConfig(){};
  int init(std::string fname) override;
  std::string SCESwitchBehaviour(bool trig = false) const;
  std::vector<std::string> get_PBSwOff_Evts() const { return _PBSwOff_Evts; };
  std::vector<std::string> get_PBSwOff_States() const { return _PBSwOff_States; };
  std::vector<std::string> get_PBSwOff_Mods() const { return _PBSwOff_Mods; };

  int do_PBSwOff_Evts(std::map<std::string, std::string>& cycle_row);
  int do_PBSwOff_States(std::map<std::string, std::string>& cycle_row);
  int do_PBSwOff_Mods(std::map<std::string, std::string>& cycle_row);

  std::string get_PBPresent(const std::map<std::string, std::string>& cycle_row) const;

protected:
  int get_ScTSwitch_Off() const { return _ScTSwitch_Off; };

private:
  int _ScTSwitch_Off = 0;
  std::vector<std::string> _PBSwOff_Evts;
  std::vector<std::string> _PBSwOff_States;
  std::vector<std::string> _PBSwOff_Mods;
};

} // namespace io
