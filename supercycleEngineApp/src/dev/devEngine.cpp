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
static int DLogLvl = 4;
epicsExportAddress(int, DLogLvl);

static int DPerfLvl = 4;
epicsExportAddress(int, DPerfLvl);

static int ScPeriodUs = 71428; //[us]
epicsExportAddress(int, ScPeriodUs);

static long initEngine()
{
  DPERFLOG(dperf::DEBUG1)

  static dlog::LevelTypes* const pDLogLvl = (dlog::LevelTypes*)&DLogLvl;
  dlog::Config::instance().init(pDLogLvl, cmn::tst::epics_now);

  static dperf::LevelTypes* const pDPerfLvl = (dperf::LevelTypes*)&DPerfLvl;
  dperf::Config::instance().init(pDPerfLvl);

  REGIO.cId = (epicsUInt64)round(cmn::tst::sec_now() / ScPeriodUs * 1000000);
  //io_block.cId = (epicsUInt64)round((cmn::tst::sec_now() - EPICS2020s) / ScPeriodUs * 1000000);
  //io_block.cId = (epicsUInt64)1099511627776;
  //io_block.cId = 0;
  REGIO.init();

  DLOG(dlog::INFO, << " cmn::compiler::info " << cmn::compiler::info())
  DLOG(dlog::INFO, << " SCE::SwVer " << dev::ObjReg::instance().get("SCE", "SwVer")())
  DLOG(dlog::INFO, << " DLogLvl " << DLogLvl << " DPerfLvl " << DPerfLvl << " ScPeriodUs " << ScPeriodUs)

  return 0;
}

static long ioEngine(aSubRecord* prec)
{
  static std::map<std::string, std::string> cycle_row_prev = {};
  //---------------------------
  DPERFLOG(dperf::DEBUG)
  //---------------------------
  // Read the cycle
  std::map<std::string, std::string> cycle_row_now = REGIO.CSVReader.getRowMap();
  //Print the cycle content
  DLOG(dlog::DEBUG, << " cycle_row " << cycle_row_now)
  // Apply the flow: e0,d1,e1,d2
  cycle::stats(REGIO);
  // Update the meta
  epicsUInt64* pvalaU64 = (epicsUInt64*)prec->vala;
  epicsUInt32* pvalaU32 = (epicsUInt32*)prec->vala;
  pvalaU64[0] = (epicsUInt64)REGIO.cId; // 0,1
  pvalaU32[2] = (epicsUInt32)REGIO.cPeriod;
  pvalaU32[3] = (epicsUInt32)REGIO.CSVReader.getRowId();
  pvalaU32[4] = (epicsUInt32)REGIO.CSVReader.getCycleId();

  // Update the Dbuf - neva , novb (max)
  if (!cycle_row_now.empty())
  {
    cycle::databuffer(REGIO, cycle_row_now);
    prec->nevb = cmn::vec2p<epicsUInt32>(prec->valb, REGIO.dbuf.vallist());
  }

  if (!cycle_row_prev.empty())
  {
    cycle::sequence(REGIO.Seq, cycle_row_prev);
    prec->nevc = cmn::vec2p<epicsUInt32>(prec->valc, REGIO.Seq.getSeqTst());
    prec->nevd = cmn::vec2p<epicsUInt32>(prec->vald, REGIO.Seq.getSeqEvt());
    prec->neve = cmn::vec2p<epicsUInt32>(prec->vale, REGIO.Seq.getSeqVec());
  }

  cycle_row_prev = cycle_row_now;
  return 0;
}

// Register the function
extern "C"
{
  epicsRegisterFunction(initEngine);
  epicsRegisterFunction(ioEngine);
}
