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
    io::LOG(io::DEBUG2) << "YmlNode::init() fname" << fname;
    filename = fname;
    node = YAML::LoadFile(filename);

    for (auto const &it : node)
      memberNames.push_back(it.first.as<std::string>());

    io::LOG(io::DEBUG) << "YmlNode::init() node " << node << " memberNames " << cmn::vec2str<std::string>(memberNames);
    return 0;
  }

  int YmlNode::init(std::string fname, std::string nodeName)
  {
    io::LOG(io::DEBUG2) << "YmlNode::init() fname " << fname << " nodeName " << nodeName;
    filename = fname;

    YAML::Node node_tmp = YAML::LoadFile(filename);
    node = node_tmp[nodeName];

    for (auto const &it : node)
      memberNames.push_back(it.first.as<std::string>());

    io::LOG(io::DEBUG) << "YmlNode::init() node " << node << " memberNames " << cmn::vec2str<std::string>(memberNames);
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

    io::LOG(io::DEBUG2) << "YmlSCEConfig::init() fname " << fname;

    inhEvtv = node["Inhibit"]["Evts"].as<std::vector<std::string>>();
    inhStatev = node["Inhibit"]["States"].as<std::vector<std::string>>();
    SCESwitchOffCycles = node["SCSwitch"]["Off"].as<int>();

    io::LOG(io::INFO) << "YmlSCEConfig::init() inhEvtv " << cmn::vec2str<std::string>(inhEvtv) << " inhStatev " << cmn::vec2str<std::string>(inhStatev);
    return 0;
  }

  int YmlKeyValMap::init(std::string fname, std::string valName)
  {
    if (YmlNode::init(fname) != 0)
      return 1;

    Yml2Map(mapsi, valName);
    io::LOG(io::INFO) << "YmlKeyValMap::init()"
                      << " fname " << fname << " valName " << valName << " mapsi " << cmn::map2str<std::string, epicsUInt32>(mapsi);

    return 0;
  }

  std::string YmlSCEConfig::SCESwitchBehaviour(bool trig)
  {
    static int counterdown = getSCESwitchOffCycles();
    static bool trig_level = false;

    if (trig_level == true)
      counterdown--;

    if (counterdown < 0)
    {
      counterdown = getSCESwitchOffCycles();
      trig_level = false;
    }

    if (trig == true)
    {
      counterdown = getSCESwitchOffCycles();
      trig_level = true;
    }

    if (trig_level == true)
      return "Off";

    return {};
  }

  int YmlKeyValMap::init(std::string fname, std::string nodeName, std::string valName)
  {
    if (YmlNode::init(fname, nodeName) != 0)
      return 1;

    Yml2Map(mapsi, valName);
    io::LOG(io::INFO) << "YmlKeyValMap::init()"
                      << " fname " << fname << " nodeName " << nodeName << " valName " << valName << " mapsi " << cmn::map2str<std::string, epicsUInt32>(mapsi);

    return 0;
  }

  int YmlDatabuffer::init(std::string fname)
  {
    io::LOG(io::INFO) << "YmlDatabuffer::init fname " << fname;
    YAML::Node node_tmp = YAML::LoadFile(fname);
    ProtVer = node_tmp["ProtVer"].as<uint>();
    ProtNum = node_tmp["ProtNum"].as<uint>();

    PBStateIds_yml.init(fname);
    PBModIds_yml.init(fname);
    PBDestIds_yml.init(fname);
    return 0;
  }

} // namespace io

// YAML::Node node1 = YAML::LoadFile("/opt/reftabs/init/databuffer-ess.yml");
// YAML::Node node2 = node1["PBState"];
// std::cout << node2 << std::endl;
