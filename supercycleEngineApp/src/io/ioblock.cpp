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

  DLOG(dlog::INFO, << " DBufCfgPath " << devio::getDbufCfgPath() << " MEvtsCfgPath " << devio::getMEvtsCfgPath() << " ScECfgPath " << devio::getScECfgPath() << " getScTablePath() " << devio::getScTablePath())

  DBuf_yml.init(devio::getDbufCfgPath());
  SCEConfig_yml.init(devio::getScECfgPath());
  mEvts_yml.init(devio::getMEvtsCfgPath());
  //Managed by the ScTable switch
  //CSVTab.init(getSCTableLink());
  Seq.init(mEvts_yml.getMap());

  return 0;
}

IOBlock& RegisteredIOBlock()
{
  static IOBlock io_block;
  return io_block;
}

} // namespace io
