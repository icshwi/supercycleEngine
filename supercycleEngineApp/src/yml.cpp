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

    inhevtv = node["inhibitEvts"].as<std::vector<std::string>>();

    io::LOG(io::INFO) << "YmlInhibitEvt::init() cmn::map2str<std::string,uint>(evtm) " << cmn::vec2str<std::string>(inhevtv);
    return 0;
  }

  std::vector<std::string> YmlInhibitEvt::getInhEvt()
  {
    io::LOG(io::DEBUG2) << "YmlInhibitEvt::getInhEvt()";

    return inhevtv;
  }

} // namespace io
