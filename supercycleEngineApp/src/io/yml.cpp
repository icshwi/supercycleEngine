/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-10-12
 */

#include "yml.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

#include <yaml-cpp/yaml.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace io
{

  int YmlNode::init(std::string fname)
  {
    dlog::Print(dlog::DEBUG2) << "YmlNode::init() fname" << fname;
    filename = fname;
    node = YAML::LoadFile(filename);

    for (auto const &it : node)
      memberNames.push_back(it.first.as<std::string>());

    dlog::Print(dlog::DEBUG) << "YmlNode::init() node " << node << " memberNames " << memberNames;
    return 0;
  }

  int YmlNode::init(std::string fname, std::string nodeName)
  {
    dlog::Print(dlog::DEBUG2) << "YmlNode::init() fname " << fname << " nodeName " << nodeName;
    filename = fname;

    YAML::Node node_tmp = YAML::LoadFile(filename);
    node = node_tmp[nodeName];

    for (auto const &it : node)
      memberNames.push_back(it.first.as<std::string>());

    dlog::Print(dlog::DEBUG) << "YmlNode::init() node " << node << " memberNames " << memberNames;
    return 0;
  }

  void YmlNode::Yml2Map(std::map<std::string, std::string> &argm, std::string key)
  {
    for (auto const &it : memberNames)
    {
      argm[it] = node[it][key].as<std::string>();
    }
  }

  void YmlNode::Yml2Map(std::map<std::string, epicsUInt32> &argm, std::string key)
  {
    for (auto const &it : memberNames)
    {
      argm[it] = node[it][key].as<epicsUInt32>();
    }
  }

  int YmlSCEConfig::init(std::string fname)
  {
    if (YmlNode::init(fname) != 0)
      return 1;

    dlog::Print(dlog::DEBUG2) << "YmlSCEConfig::init() fname " << fname;

    m_PBSwOff_Evts = node["PBSwOff"]["Evts"].as<std::vector<std::string>>();
    m_PBSwOff_States = node["PBSwOff"]["States"].as<std::vector<std::string>>();
    m_PBSwOff_Mods = node["PBSwOff"]["Mods"].as<std::vector<std::string>>();

    m_ScTSwitch_Off = node["ScTSwitch"]["Off"].as<int>();

    dlog::Print(dlog::INFO) << "YmlSCEConfig::init() m_PBSwOff_Evts " << m_PBSwOff_Evts << " m_PBSwOff_States " << m_PBSwOff_States << " m_PBSwOff_Mods " << m_PBSwOff_Mods;

    return 0;
  }

  int YmlKeyValMap::init(std::string fname, std::string valName)
  {
    if (YmlNode::init(fname) != 0)
      return 1;

    Yml2Map(mapsi, valName);
    dlog::Print(dlog::INFO) << "YmlKeyValMap::init()"
                            << " fname " << fname << " valName " << valName << " mapsi " << mapsi;

    return 0;
  }

  std::string YmlSCEConfig::SCESwitchBehaviour(bool trig)
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

  int YmlSCEConfig::do_PBSwOff_Evts(std::map<std::string, std::string> &cycle_row)
  {
    for (auto &it : get_PBSwOff_Evts())
      cycle_row.erase(it);

    return 0;
  }

  int YmlSCEConfig::do_PBSwOff_States(std::map<std::string, std::string> &cycle_row)
  {
    for (auto &state : get_PBSwOff_States())
      if (cycle_row["PBState"] == state)
        for (auto &it : get_PBSwOff_Evts())
          cycle_row.erase(it);

    return 0;
  }

  int YmlSCEConfig::do_PBSwOff_Mods(std::map<std::string, std::string> &cycle_row)
  {
    for (auto &state : get_PBSwOff_Mods())
      if (cycle_row["PBMod"] == state)
        for (auto &it : get_PBSwOff_Evts())
          cycle_row.erase(it);

    return 0;
  }

  std::string YmlSCEConfig::get_PBPresent(std::map<std::string, std::string> &cycle_row)
  {
    std::size_t cnt = 0;

    for (auto const &it : get_PBSwOff_Evts())
      if (cycle_row.count(it) == 0)
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
    dlog::Print(dlog::INFO) << "YmlKeyValMap::init()"
                            << " fname " << fname << " nodeName " << nodeName << " valName " << valName << " mapsi " << mapsi;

    return 0;
  }

  int YmlDatabuffer::init(std::string fname)
  {
    dlog::Print(dlog::INFO) << "YmlDatabuffer::init fname " << fname;
    YAML::Node node_tmp = YAML::LoadFile(fname);
    m_ProtVer = node_tmp["ProtVer"].as<uint>();
    m_ProtNum = node_tmp["ProtNum"].as<uint>();

    m_PBStateIds.init(fname);
    m_PBModIds.init(fname);
    m_PBDestIds.init(fname);
    m_PBPresentIds.init(fname);
    return 0;
  }

} // namespace io

// YAML::Node node1 = YAML::LoadFile("/opt/reftabs/init/databuffer-ess.yml");
// YAML::Node node2 = node1["PBState"];
// std::cout << node2 << std::endl;
