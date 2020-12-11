/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <registryFunction.h>

#include "cmnbase.hpp"
#include "cycle.hpp"
#include "devStringoutCtrl.hpp"
#include "dlog.hpp"
#include "ioblock.hpp"

#include "cmdMapStrOut.hpp"
#include "dperf.hpp"
#include "object.hpp"

//int and double only
static int iodebug = 4;
epicsExportAddress(int, iodebug);

static int dperflvl = 4;
epicsExportAddress(int, dperflvl);

static int PscUs = 71428; //[us]
epicsExportAddress(int, PscUs);

static int sctableSwitch(io::IOBlock& io)
{
  if (io.getSCTableLink().compare(io._CSVStrMap.getFile()) != 0)
  {
    DLOG(dlog::INFO, << " OLD io._CSVStrMap.getFile() " << io._CSVStrMap.getFile() << " NEW io.getSCTableLink() " << io.getSCTableLink())

    io._CSVStrMap.init(io.getSCTableLink());

    // Trigger sctable switch behaviour
    io.SCEConfig_yml.SCESwitchBehaviour(true);
  }
  return 0;
}

static long initEngine()
{
  DPERFTIMERSCOPE(dperf::DEBUG1);

  static dlog::LevelTypes* const piodebug = (dlog::LevelTypes*)&iodebug;
  dlog::Config::instance().init(piodebug, cmn::tst::epics_now);

  static dperf::LevelTypes* const dperflvlp = (dperf::LevelTypes*)&dperflvl;
  dperf::Config::instance().init(dperflvlp);

  io::RegisteredIOBlock().cId = (epicsUInt64)round(cmn::tst::sec_now() / PscUs * 1000000);
  //io_block.cId = (epicsUInt64)round((cmn::tst::sec_now() - EPICS2020s) / PscUs * 1000000);
  //io_block.cId = (epicsUInt64)1099511627776;
  //io_block.cId = 0;
  io::RegisteredIOBlock().init(RegisteredCmdMapStrOut);

  DLOG(dlog::INFO, << " cmn::compiler::info " << cmn::compiler::info())
  DLOG(dlog::INFO, << " SCE::SwVer " << dev::ObjReg::instance().get("SCE", "SwVer")())
  DLOG(dlog::INFO, << " iodebug " << iodebug << " PscUs " << PscUs)

  return 0;
}

static long ioEngine(aSubRecord* prec)
{
  static std::map<std::string, std::string> cycle_row_prev = {};
  //---------------------------
  DPERFTIMERSCOPE(dperf::DEBUG);
  //---------------------------
  // Configure new cycle
  io::RegisteredIOBlock().dbSync(RegisteredStrOutMap);
  // Read the cycle
  std::map<std::string, std::string> cycle_row_now = io::RegisteredIOBlock()._CSVStrMap.getRowMap();
  //Print the cycle content
  DLOG(dlog::DEBUG, << " cycle_row " << cycle_row_now)
  // Apply the flow: e0,d1,e1,d2
  cycle::stats(io::RegisteredIOBlock());
  // Update the meta
  epicsUInt64* pvalaU64 = (epicsUInt64*)prec->vala;
  epicsUInt32* pvalaU32 = (epicsUInt32*)prec->vala;
  pvalaU64[0] = (epicsUInt64)io::RegisteredIOBlock().cId; // 0,1
  pvalaU32[2] = (epicsUInt32)io::RegisteredIOBlock().cPeriod;
  pvalaU32[3] = (epicsUInt32)io::RegisteredIOBlock()._CSVStrMap.getRowId();
  pvalaU32[4] = (epicsUInt32)io::RegisteredIOBlock()._CSVStrMap.getCycleId();

  // Update the Dbuf - neva , novb (max)
  if (!cycle_row_now.empty())
  {
    cycle::databuffer(io::RegisteredIOBlock(), cycle_row_now);
    prec->nevb = cmn::vec2p<epicsUInt32>(prec->valb, io::RegisteredIOBlock().dbuf.vallist());
  }

  if (!cycle_row_prev.empty())
  {
    cycle::sequence(io::RegisteredIOBlock().Seq, cycle_row_prev);
    prec->nevc = cmn::vec2p<epicsUInt32>(prec->valc, io::RegisteredIOBlock().Seq.getSeqTst());
    prec->nevd = cmn::vec2p<epicsUInt32>(prec->vald, io::RegisteredIOBlock().Seq.getSeqEvt());
    prec->neve = cmn::vec2p<epicsUInt32>(prec->vale, io::RegisteredIOBlock().Seq.getSeqVec());
  }

  cycle_row_prev = cycle_row_now;
  // Change the table if requested and use the post processing free time
  sctableSwitch(io::RegisteredIOBlock());
  return 0;
}

// Register the function
extern "C"
{
  epicsRegisterFunction(initEngine);
  epicsRegisterFunction(ioEngine);
}
