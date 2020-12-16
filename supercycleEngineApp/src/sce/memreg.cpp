/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "devIO.hpp"

#include "cmnbase.hpp"
#include "dlog.hpp"
#include "memreg.hpp"

#include <iostream>

namespace mem
{

int ScERegistry::init()
{

  DLOG(dlog::INFO, << " getDBufCfgPath " << devio::getDBufCfgPath() << " MEvtsCfgPath " << devio::getMEvtsCfgPath() << " ScECfgPath " << devio::getScECfgPath() << " getScTablePath() " << devio::getScTablePath())

  DBuf.init(devio::getDBufCfgPath());
  Config.init(devio::getScECfgPath());
  MEvts.init(devio::getMEvtsCfgPath());
  //Managed by the ScTable switch
  CSVHandler.init(devio::getScTablePath());
  SeqHandler.init(MEvts.getMap());

  return 0;
}

ScERegistry& RegisteredIOBlock()
{
  static ScERegistry io_block;
  return io_block;
}

} // namespace mem
