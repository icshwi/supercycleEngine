/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "iocVars.hpp"
#include "ioblock.hpp"
#include "iocsh.h"
#include "cmdMapStrOut.hpp"
#include "dlog.hpp"
#include "object.hpp"

#include <cmath>
#include <epicsExport.h>

//int and double only
static int iodebug = 4;
epicsExportAddress(int, iodebug);

static int PscUs = 71428; //[us]
epicsExportAddress(int, PscUs);

void iocVars2IO()
{
  static dlog::Type *const piodebug = (dlog::Type *)&iodebug;

  dlog::Config::instance().init(piodebug, cmn::tst::epics_now);

  io::RegisteredIOBlock().cId = (epicsUInt64)round(cmn::tst::sec_now() / PscUs * 1000000);
  //io_block.cId = (epicsUInt64)round((cmn::tst::sec_now() - EPICS2020s) / PscUs * 1000000);
  //io_block.cId = (epicsUInt64)1099511627776;
  //io_block.cId = 0;
  io::RegisteredIOBlock().init(RegisteredCmdMapStrOut);

  dlog::Print(dlog::INFO) << "iocVars2IO() SCE::SwVer " << dev::ObjReg::instance().get("SCE", "SwVer")();
  dlog::Print(dlog::INFO) << "iocVars2IO() iodebug " << iodebug << " PscUs " << PscUs;
}
