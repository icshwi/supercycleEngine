/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "devIO.hpp"

#include "cmnbase.hpp"
#include "dlog.hpp"
#include "ioblock.hpp"

#include <iostream>

namespace io
{

int IOBlock::init()
{

  DLOG(dlog::INFO, << " DBufCfgPath " << devio::getDbufCfgPath() << " MEvtsCfgPath " << devio::getMEvtsCfgPath() << " ScECfgPath " << devio::getScECfgPath() << " getScTablePath() " << getScTablePath())

  DBuf_yml.init(devio::getDbufCfgPath());
  SCEConfig_yml.init(devio::getScECfgPath());
  mEvts_yml.init(devio::getMEvtsCfgPath());
  //Managed by the ScTable switch
  //CSVTab.init(getSCTableLink());
  Seq.init(mEvts_yml.getMap());

  return 0;
}

int IOBlock::dbSync(const std::map<std::string, std::string>& argms)
{

  for (auto const& it : argms)
  {
    if (it.first.find(GETVARNAME(ScTable)) != std::string::npos)
      ScTable = it.second;
    else if (it.first.find(GETVARNAME(PBState)) != std::string::npos)
      PBState = it.second;
    else if (it.first.find(GETVARNAME(PBMod)) != std::string::npos)
      PBMod = it.second;
    else if (it.first.find(GETVARNAME(PBDest)) != std::string::npos)
      PBDest = it.second;
  }
  //std::cout << argms << std::endl;
  return 0;
}

IOBlock& RegisteredIOBlock()
{
  static IOBlock io_block;
  return io_block;
}

} // namespace io
