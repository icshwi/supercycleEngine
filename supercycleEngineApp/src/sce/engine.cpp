/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "engine.hpp"
#include "cmnbase.hpp"
#include "dlog.hpp"

#include "dbuf.hpp"
#include "seq.hpp"
#include "yml.hpp"

#include "scenv.hpp"

static void io_dbuf_safe_write(sce::DBufPacket& dbuf, const std::map<std::string, std::string>& row, const env::DBFIDX idx)
{
  try
  {
    dbuf.write(idx, std::stol(row.at(env::DBFIDX2Str.at(idx))));
  }
  catch (...)
  {
    dbuf.write(idx, 0); // Worse case selected so that the beam is on
    DLOG(dlog::WARNING, << " wrong_idx_value env::DBFIDX2Str.at(idx) " << env::DBFIDX2Str.at(idx))
  }
}

static void io_dbuf_safe_write(sce::DBufPacket& dbuf, const std::map<std::string, std::string>& row, const env::DBFIDX idx, const std::map<std::string, epicsUInt32>& mapValKey)
{
  try
  {
    dbuf.write(idx, mapValKey.at(row.at(env::DBFIDX2Str.at(idx))));
  }
  catch (...)
  {
    dbuf.write(idx, 0); // Worse case selected so that the beam is on
    DLOG(dlog::WARNING, << " wrong_idx_value env::DBFIDX2Str.at(idx) " << env::DBFIDX2Str.at(idx))
  }
}

static void io_dbuf_safe_write_all(io::IOBlock& io, const std::map<std::string, std::string>& cycle_row)
{
  io.dbuf.clear();
  // ProtNum
  io.dbuf.write(env::ProtNum, io.DBuf_yml.getProtNum());
  // ProtVer
  io.dbuf.write(env::ProtVer, io.DBuf_yml.getProtVer());
  // IdCycle
  io.dbuf.write(env::IdCycle, (epicsUInt32)io.cId);             //low 4bytes
  io.dbuf.write(env::IdCycle + 4, (epicsUInt32)(io.cId >> 32)); //high 4bytes
  // PBState
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBState, io.DBuf_yml._PBStateIds.getMap());
  // PBDest
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBDest, io.DBuf_yml._PBDestIds.getMap());
  // PBMod
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBMod, io.DBuf_yml._PBModIds.getMap());
  // PBPresent
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBPresent, io.DBuf_yml._PBPresentIds.getMap());
  // PBLen
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBLen);
  // PBEn
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBEn);
  // PBCurr
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBCurr);
}

static void cycle_row_insert(std::map<std::string, std::string>& rowm, const std::map<std::string, std::string>& argm)
{
  rowm.insert(argm.begin(), argm.end());
}

int engineCycle(io::IOBlock& io)
{
  static epicsUInt32 tst = 0; // The timestamp holder
  std::map<std::string, std::string> prev_cycle_row;
  // Start the cycle
  // ===============
  io.cPeriod = cmn::tst::period_us(tst);
  io.cId++;
  DLOG(dlog::DEBUG, << " ScTableCycleId " << io._CSVStrMap.getCycleId() << " ScTableRowId " << io._CSVStrMap.getRowId() << " io.cId " << io.cId << " io.cPeriod " << io.cPeriod)
  // ----------------------------------
  std::map<std::string, std::string> cycle_row = io._CSVStrMap.getRowMap();
  //Do not do anything if the cycle is not ready
  if (cycle_row.empty())
    return 0;

  // Write other cycle variables
  std::map<std::string, std::string> cycle_row_adds = {};
  // cycle_row_adds[env::EVT2Str.at(env::COFFSET)] = cmn::str::convert(io.cOffset);
  // Insert generated cycle variables into the cycle row
  cycle_row_insert(cycle_row, cycle_row_adds);

  // Remove beam generation depending on the selected behaviour
  if ("Off" == io.SCEConfig_yml.SCESwitchBehaviour())
    io.SCEConfig_yml.do_PBSwOff_Evts(cycle_row);

  // SCTABLE operations
  // PBState
  cycle_row["PBState"] = io.getPBState();
  io.SCEConfig_yml.do_PBSwOff_States(cycle_row);
  // PBDest
  cycle_row["PBDest"] = io.getPBDest();
  // PBMod
  cycle_row["PBMod"] = io.getPBMod();
  io.SCEConfig_yml.do_PBSwOff_Mods(cycle_row);
  if (cycle_row["PBMod"] == "NoBeam")
    cycle_row["PBState"] = "Off";
  // PBPresent
  cycle_row["PBPresent"] = io.SCEConfig_yml.get_PBPresent(cycle_row);

  //Print the log
  DLOG(dlog::DEBUG, << " cycle_row " << cycle_row)

  // Update the event sequence container
  io.Seq.write(cycle_row);
  // Update the data buffer container
  io_dbuf_safe_write_all(io, cycle_row);

  //Print the log
  DLOG(dlog::DEBUG, << " io.SEQ.getSeq " << io.Seq.getSeqMap())
  DLOG(dlog::DEBUG, << " io.dbuf.getDbuf " << io.dbuf.getDbuf())

  prev_cycle_row = cycle_row;
  return 0;
}
