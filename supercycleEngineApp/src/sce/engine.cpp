/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "engine.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

#include "dbuf.hpp"
#include "yml.hpp"
#include "seq.hpp"

#include "scenv.hpp"

static void io_dbuf_safe_write(sce::DBufPacket &dbuf, std::map<std::string, std::string> &row, env::DBFIDX idx)
{
  try
  {
    dbuf.write(idx, std::stol(row[env::DBFIDX2Str.at(idx)]));
  }
  catch (...)
  {
    dbuf.write(idx, 0); // Worse case selected so that the beam is on
    dlog::Print(dlog::WARNING) << "writeDbufSafe() idx not defined!, env::DBFIDX2Str.at(idx) " << env::DBFIDX2Str.at(idx);
  }
}

static void io_dbuf_safe_write(sce::DBufPacket &dbuf, std::map<std::string, std::string> &row, const env::DBFIDX idx, std::map<std::string, epicsUInt32> mapValKey)
{
  try
  {
    dbuf.write(idx, mapValKey[row[env::DBFIDX2Str.at(idx)]]);
  }
  catch (...)
  {
    dbuf.write(idx, 0); // Worse case selected so that the beam is on
    dlog::Print(dlog::WARNING) << "writeDbufSafe() idx not defined!, env::DBFIDX2Str.at(idx) " << env::DBFIDX2Str.at(idx);
  }
}

static void cycle_row_insert(std::map<std::string, std::string> &rowm, std::map<std::string, std::string> argm)
{
  rowm.insert(argm.begin(), argm.end());
}

static std::string getPBPresent(const std::map<std::string, std::string> &cycle_row, const std::vector<std::string> inh_evts)
{
  std::size_t cnt = 0;

  for (auto const &it : inh_evts)
    if (cycle_row.count(it) == 0)
      cnt++;

  if (cnt == inh_evts.size())
    return "Off";

  return "On";
}

int engineCycle(io::IOBlock &io)
{
  static epicsUInt32 tst = 0; // The timestamp holder
  // Start the cycle
  // ===============
  std::map<std::string, std::string> cycle_row = io.m_CSVStrMap.getRowMap();

  io.cPeriod = cmn::tst::period_us(tst);
  io.cId++;
  dlog::Print(dlog::DEBUG) << "engineCycle()"
                           << " row it " << io.m_CSVStrMap.getRowId() << " io.cId " << io.cId << " io.cPeriod " << io.cPeriod;

  // Write other cycle variables
  std::map<std::string, std::string> cycle_row_adds = {};
  // cycle_row_adds[env::EVT2Str.at(env::COFFSET)] = cmn::str::convert(io.cOffset);
  // Insert generated cycle variables into the cycle row
  cycle_row_insert(cycle_row, cycle_row_adds);

  // Remove beam generation depending on the selected behaviour
  if ("Off" == io.SCEConfig_yml.SCESwitchBehaviour())
    io.SCEConfig_yml.do_PBSwOff_Evts(cycle_row);

  // Update the databuffer container

  io.dbuf.clear();
  // ProtNum
  io.dbuf.write(env::ProtNum, io.DBuf_yml.getProtNum());
  // ProtVer
  io.dbuf.write(env::ProtVer, io.DBuf_yml.getProtVer());
  // IdCycle
  io.dbuf.write(env::IdCycle, (epicsUInt32)io.cId);             //low 4bytes
  io.dbuf.write(env::IdCycle + 4, (epicsUInt32)(io.cId >> 32)); //high 4bytes

  // SCTABLE operations

  // PBState
  cycle_row["PBState"] = io.getPBState();
  io.SCEConfig_yml.do_PBSwOff_States(cycle_row);
  // Erase inhibit events from the cycle in regards to the state
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBState, io.DBuf_yml.m_PBStateIds.getMap());

  // PBDest
  cycle_row["PBDest"] = io.getPBDest();
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBDest, io.DBuf_yml.m_PBDestIds.getMap());
  // PBMod
  cycle_row["PBMod"] = io.getPBMod();
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBMod, io.DBuf_yml.m_PBModIds.getMap());
  // PBPresent
  cycle_row["PBPresent"] = getPBPresent(cycle_row, io.SCEConfig_yml.get_PBSwOff_Evts());
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBPresent, io.DBuf_yml.m_PBPresentIds.getMap());
  // PBLen
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBLen);
  // PBEn
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBEn);
  // PBCurr
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBCurr);

  // Update the event sequence container
  io.Seq.write(cycle_row);

  //Check the buffer
  dlog::Print(dlog::DEBUG) << "engineCycle() io.SEQ.getSeq() " << io.Seq.getSeqMap() << " io.dbuf.getDbuf() " << io.dbuf.getDbuf();

  return 0;
}
