/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "cmnbase.hpp"
#include "devStringoutCtrl.hpp"
#include "dlog.hpp"

#include "cmdMapStrOut.hpp"
#include "object.hpp"

//int and double only
static int iodebug = 4;
epicsExportAddress(int, iodebug);

static int PscUs = 71428; //[us]
epicsExportAddress(int, PscUs);

static int sctableSwitch(io::IOBlock &io)
{
  if (io.getSCTableLink().compare(io.m_CSVStrMap.getFile()) != 0)
  {
    dlog::Print(dlog::DEBUG) << "engineCycle() OLD io.m_CSVStrMap.getFile() " << io.m_CSVStrMap.getFile()
                             << " NEW io.getSCTableLink() " << io.getSCTableLink();

    io.m_CSVStrMap.init(io.getSCTableLink());

    // Trigger sctable switch behaviour
    io.SCEConfig_yml.SCESwitchBehaviour(true);
  }
  return 0;
}

static long initEngine()
{
  static dlog::Type *const piodebug = (dlog::Type *)&iodebug;
  dlog::Config::instance().init(piodebug, cmn::tst::epics_now);

  io::RegisteredIOBlock().cId = (epicsUInt64)round(cmn::tst::sec_now() / PscUs * 1000000);
  //io_block.cId = (epicsUInt64)round((cmn::tst::sec_now() - EPICS2020s) / PscUs * 1000000);
  //io_block.cId = (epicsUInt64)1099511627776;
  //io_block.cId = 0;
  io::RegisteredIOBlock().init(RegisteredCmdMapStrOut);

  dlog::Print(dlog::INFO) << "initEngine SCE::SwVer " << dev::ObjReg::instance().get("SCE", "SwVer")();
  dlog::Print(dlog::INFO) << "initEngine iodebug " << iodebug << " PscUs " << PscUs;

  return 0;
}

static long ioEngine(aSubRecord *prec)
{
  // Configure new cycle
  io::RegisteredIOBlock().dbSync(RegisteredStrOutMap);
  // Change the table if requested
  sctableSwitch(io::RegisteredIOBlock());
  // Engine cycle
  engineCycle(io::RegisteredIOBlock());
  // Update the meta
  epicsUInt64 *pvalaU64 = (epicsUInt64 *)prec->vala;
  epicsUInt32 *pvalaU32 = (epicsUInt32 *)prec->vala;
  pvalaU64[0] = (epicsUInt64)io::RegisteredIOBlock().cId; // 0,1
  pvalaU32[2] = (epicsUInt32)io::RegisteredIOBlock().cPeriod;
  pvalaU32[3] = (epicsUInt32)io::RegisteredIOBlock().m_CSVStrMap.getRowId();
  // Update the Dbuf - neva , novb (max)
  prec->nevb = cmn::vec2p<epicsUInt32>(prec->valb, io::RegisteredIOBlock().dbuf.vallist());
  prec->nevc = cmn::vec2p<epicsUInt32>(prec->valc, io::RegisteredIOBlock().Seq.getSeqTst());
  prec->nevd = cmn::vec2p<epicsUInt32>(prec->vald, io::RegisteredIOBlock().Seq.getSeqEvt());
  prec->neve = cmn::vec2p<epicsUInt32>(prec->vale, io::RegisteredIOBlock().Seq.getSeqVec());

  return 0;
}

// Register the function
extern "C"
{
  epicsRegisterFunction(initEngine);
  epicsRegisterFunction(ioEngine);
}
