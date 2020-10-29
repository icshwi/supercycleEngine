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

    io::LOG(io::DEBUG) << "YmlNode::init() node " << node;
    io::LOG(io::DEBUG) << "YmlNode::init() memberNames " << cmn::vec2str<std::string>(memberNames);
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

  int YmlInhibitEvt::init(std::string fname)
  {
    if (YmlNode::init(fname) != 0)
      return 1;

    io::LOG(io::DEBUG2) << "YmlInhibitEvt::init() fname " << fname;

    inhEvtv = node["inhEvts"].as<std::vector<std::string>>();
    inhStatev = node["inhStates"].as<std::vector<std::string>>();

    io::LOG(io::INFO) << "YmlInhibitEvt::init() inhEvtv " << cmn::vec2str<std::string>(inhEvtv);
    io::LOG(io::INFO) << "YmlInhibitEvt::init() inhStatev " << cmn::vec2str<std::string>(inhStatev);
    return 0;
  }

  int YmlMEvt::init(std::string fname)
  {
    if (YmlNode::init(fname) != 0)
      return 1;

    io::LOG(io::DEBUG2) << "YmlMEvt::init() fname " << fname;

    Yml2Map(evtm, "id");
    io::LOG(io::INFO) << "YmlMEvt::init() evtm " << cmn::map2str<std::string, epicsUInt32>(evtm);

    return 0;
  }

} // namespace io
