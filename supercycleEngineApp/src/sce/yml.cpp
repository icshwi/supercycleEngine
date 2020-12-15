/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-10-12
 */

#include "yml.hpp"
#include "cmnbase.hpp"
#include "dlog.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace sce
{

int YmlNode::init(std::string fname)
{
  _filename = fname;
  _node = YAML::LoadFile(_filename);

  for (auto const& it : _node)
    _memberNames.push_back(it.first.as<std::string>());

  DLOG(dlog::DEBUG, << " fname " << fname << " _node " << _node << " _memberNames " << _memberNames)
  return 0;
}

int YmlNode::init(std::string fname, std::string nodeName)
{
  _filename = fname;

  YAML::Node node_tmp = YAML::LoadFile(_filename);
  _node = node_tmp[nodeName];

  for (auto const& it : _node)
    _memberNames.push_back(it.first.as<std::string>());

  DLOG(dlog::DEBUG, << " fname " << fname << " nodeName " << nodeName << " _node " << _node << " _memberNames " << _memberNames)
  return 0;
}

void YmlNode::Yml2Map(std::map<std::string, std::string>& argm, std::string key)
{
  for (auto const& it : _memberNames)
  {
    argm[it] = _node[it][key].as<std::string>();
  }
}

void YmlNode::Yml2Map(std::map<std::string, epicsUInt32>& argm, std::string key)
{
  for (auto const& it : _memberNames)
  {
    argm[it] = _node[it][key].as<epicsUInt32>();
  }
}

int YmlSCEConfig::init(std::string fname)
{
  if (YmlNode::init(fname) != 0)
    return 1;

  _PBSwOff_Evts = _node["PBSwOff"]["Evts"].as<std::vector<std::string>>();
  _PBSwOff_States = _node["PBSwOff"]["States"].as<std::vector<std::string>>();
  _PBSwOff_Mods = _node["PBSwOff"]["Mods"].as<std::vector<std::string>>();

  _ScTSwitch_Off = _node["ScTSwitch"]["Off"].as<int>();

  DLOG(dlog::INFO, << " fname " << fname << " _PBSwOff_Evts " << _PBSwOff_Evts << " _PBSwOff_States " << _PBSwOff_States << " _PBSwOff_Mods " << _PBSwOff_Mods)
  return 0;
}

int YmlKeyValMap::init(std::string fname, std::string valName)
{
  if (YmlNode::init(fname) != 0)
    return 1;

  Yml2Map(mapsi, valName);

  DLOG(dlog::INFO, << " fname " << fname << " valName " << valName << " mapsi " << mapsi)
  return 0;
}

std::string YmlSCEConfig::SCESwitchBehaviour(bool trig) const
{
  static int counterdown = get_ScTSwitch_Off();
  static bool trig_level = false;

  if (trig_level == true)
    counterdown--;

  if (counterdown < 0)
  {
    counterdown = get_ScTSwitch_Off();
    trig_level = false;
  }

  if (trig == true)
  {
    counterdown = get_ScTSwitch_Off();
    trig_level = true;
  }

  if (trig_level == true)
    return "Off";

  return {};
}

int YmlSCEConfig::do_PBSwOff_Evts(std::map<std::string, std::string>& cycle_row)
{
  for (auto& it : get_PBSwOff_Evts())
    cycle_row.erase(it);

  return 0;
}

int YmlSCEConfig::do_PBSwOff_States(std::map<std::string, std::string>& cycle_row)
{
  for (auto& state : get_PBSwOff_States())
    if (cycle_row["PBState"] == state)
      for (auto& it : get_PBSwOff_Evts())
        cycle_row.erase(it);

  return 0;
}

int YmlSCEConfig::do_PBSwOff_Mods(std::map<std::string, std::string>& cycle_row)
{
  for (auto& state : get_PBSwOff_Mods())
    if (cycle_row["PBMod"] == state)
      for (auto& it : get_PBSwOff_Evts())
        cycle_row.erase(it);

  return 0;
}

std::string YmlSCEConfig::get_PBPresent(const std::map<std::string, std::string>& cycle_row) const
{
  std::size_t cnt = 0;

  for (auto const& it : get_PBSwOff_Evts())
    if (cycle_row.count(it) > 0)
      if (cycle_row.at(it).empty() == true)
        cnt++;

  if (cnt == get_PBSwOff_Evts().size())
    return "Off";

  return "On";
}

int YmlKeyValMap::init(std::string fname, std::string nodeName, std::string valName)
{
  if (YmlNode::init(fname, nodeName) != 0)
    return 1;

  Yml2Map(mapsi, valName);

  DLOG(dlog::INFO, << " fname " << fname << " nodeName " << nodeName << " valName " << valName << " mapsi " << mapsi)
  return 0;
}

int YmlDatabuffer::init(std::string fname)
{
  DLOG(dlog::INFO, << " fname " << fname)

  YAML::Node node_tmp = YAML::LoadFile(fname);
  _ProtVer = node_tmp["ProtVer"].as<uint>();
  _ProtNum = node_tmp["ProtNum"].as<uint>();

  _PBStateIds.init(fname);
  _PBModIds.init(fname);
  _PBDestIds.init(fname);
  _PBPresentIds.init(fname);
  return 0;
}

} // namespace sce

// YAML::Node node1 = YAML::LoadFile("/opt/reftabs/init/databuffer-ess.yml");
// YAML::Node node2 = node1["PBState"];
// std::cout << node2 << std::endl;
