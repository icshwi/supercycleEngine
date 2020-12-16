/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */
#include "devIO.hpp"

#include "cycle.hpp"
//#include "cmnbase.hpp"
#include "dlog.hpp"

#include "dbuf.hpp"
#include "scenv.hpp"
#include "seq.hpp"

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

static void io_dbuf_safe_write_all(mem::ScERegistry& io, const std::map<std::string, std::string>& cycle_row)
{
  io.DBufHandler.clear();
  // ProtNum
  io.DBufHandler.write(env::ProtNum, io.DBuf.getProtNum());
  // ProtVer
  io.DBufHandler.write(env::ProtVer, io.DBuf.getProtVer());
  // IdCycle
  io.DBufHandler.write(env::IdCycle, (epicsUInt32)io.cId);             //low 4bytes
  io.DBufHandler.write(env::IdCycle + 4, (epicsUInt32)(io.cId >> 32)); //high 4bytes
  // PBState
  io_dbuf_safe_write(io.DBufHandler, cycle_row, env::PBState, io.DBuf._PBStateIds.getMap());
  // PBDest
  io_dbuf_safe_write(io.DBufHandler, cycle_row, env::PBDest, io.DBuf._PBDestIds.getMap());
  // PBMod
  io_dbuf_safe_write(io.DBufHandler, cycle_row, env::PBMod, io.DBuf._PBModIds.getMap());
  // PBPresent
  io_dbuf_safe_write(io.DBufHandler, cycle_row, env::PBPresent, io.DBuf._PBPresentIds.getMap());
  // PBLen
  io_dbuf_safe_write(io.DBufHandler, cycle_row, env::PBLen);
  // PBEn
  io_dbuf_safe_write(io.DBufHandler, cycle_row, env::PBEn);
  // PBCurr
  io_dbuf_safe_write(io.DBufHandler, cycle_row, env::PBCurr);
}

/*
static void cycle_row_insert(std::map<std::string, std::string>& rowm, const std::map<std::string, std::string>& argm)
{
  rowm.insert(argm.begin(), argm.end());
}
*/

/*
TODO: write cycle variables for the future
{
    // Write other cycle variables
  std::map<std::string, std::string> cycle_row_adds = {};
  // cycle_row_adds[env::EVT2Str.at(env::COFFSET)] = cmn::str::convert(io.cOffset);
  // Insert generated cycle variables into the cycle row
  cycle_row_insert(cycle_row, cycle_row_adds);
}
*/

namespace cycle
{

int databuffer(mem::ScERegistry& io, std::map<std::string, std::string>& cycle_row)
{
  // Remove beam generation depending on the selected behaviour
  if ("Off" == io.Config.SCESwitchBehaviour())
    io.Config.do_PBSwOff_Evts(cycle_row);

  // sctable operations
  // PBState
  cycle_row["PBState"] = devio::getPBState();
  io.Config.do_PBSwOff_States(cycle_row);
  // PBDest
  cycle_row["PBDest"] = devio::getPBDest();
  // PBMod
  cycle_row["PBMod"] = devio::getPBMod();
  io.Config.do_PBSwOff_Mods(cycle_row);
  if (cycle_row["PBMod"] == "NoBeam")
    cycle_row["PBState"] = "Off";
  // PBPresent
  cycle_row["PBPresent"] = io.Config.get_PBPresent(cycle_row);

  // Update the data buffer container
  io_dbuf_safe_write_all(io, cycle_row);

  //Print the log
  DLOG(dlog::DEBUG, << " io.dbuf.getDbuf " << io.DBufHandler.getDbuf())

  return 0;
}

int sequence(const sce::SequenceHandler& seq, const std::map<std::string, std::string>& cycle_row)
{
  // Update the event sequence container
  seq.write(cycle_row);
  //Print the log
  DLOG(dlog::DEBUG, << " io.SEQ.getSeq " << seq.getSeqMap())

  return 0;
}

int stats(const mem::ScERegistry& io)
{
  static epicsUInt32 tst = 0; // The timestamp holder
  // State the cycle
  io.cPeriod = cmn::tst::period_us(tst);
  io.cId++;
  DLOG(dlog::DEBUG, << " io.CSVHandler.getCycleId() " << io.CSVHandler.getCycleId() << " io.CSVHandler.getRowId() " << io.CSVHandler.getRowId() << " io.cId " << io.cId << " io.cPeriod " << io.cPeriod)

  return 0;
}

} // namespace cycle
