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

    io::LOG(io::INFO) << "YmlNode::init() node " << node;
    return 0;
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

  // int YmlMEvt::init(std::string fname)
  // {
  //   if (YmlNode::init(fname) != 0)
  //     return 1;

  //   io::LOG(io::DEBUG2) << "YmlMEvt::init() fname " << fname;
  //   //evtm = node["inhibitEvts"].as<std::vector<std::string>>();
  //   //json2map(value, evtm);
  //   //io::LOG(io::INFO) << "YmlMEvt::init() cmn::map2str<std::string,uint>(evtm) " << cmn::map2str<std::string, uint>(evtm);

  //   return 0;
  // }

} // namespace io
