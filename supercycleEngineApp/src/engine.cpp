/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "engine.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

#include "dbuf.hpp"
#include "csv.hpp"
#include "yml.hpp"
#include "seq.hpp"

#include "scenv.hpp"

int sctableSwitch(io::IOBlock &io)
{
  if (io.getSCTableLink().compare(io.sctable.getFileLink()) != 0)
  {
    io::LOG(io::DEBUG) << "engineCycle() different sctable selected OLD io.sctable.getFileLink() "
                       << io.sctable.getFileLink() << " NEW io.getSCTableLink() " << io.getSCTableLink();
    io.sctable.init(io.getSCTableLink());

    // Trigger sctable switch behaviour
    io.SCEConfig_yml.SCESwitchBehaviour(true);
  }
  return 0;
}

void io_dbuf_safe_write(dbf::DBufPacket &dbuf, std::map<std::string, std::string> &row, env::DBFIDX idx)
{
  try
  {
    dbuf.write(idx, std::stol(row[env::DBFIDX2Str.at(idx)]));
  }
  catch (...)
  {
    dbuf.write(idx, 0); // Worse case selected so that the beam is on
    io::LOG(io::WARNING) << "writeDbufSafe() idx not defined!, env::DBFIDX2Str.at(idx) " << env::DBFIDX2Str.at(idx);
  }
}

void io_dbuf_safe_write(dbf::DBufPacket &dbuf, std::map<std::string, std::string> &row, env::DBFIDX idx, std::map<std::string, epicsUInt32> mapValKey)
{
  try
  {
    dbuf.write(idx, mapValKey[row[env::DBFIDX2Str.at(idx)]]);
  }
  catch (...)
  {
    dbuf.write(idx, 0); // Worse case selected so that the beam is on
    io::LOG(io::WARNING) << "writeDbufSafe() idx not defined!, env::DBFIDX2Str.at(idx) " << env::DBFIDX2Str.at(idx);
  }
}

void cycle_row_insert(std::map<std::string, std::string> &rowm, std::map<std::string, std::string> argm)
{
  rowm.insert(argm.begin(), argm.end());
}

int sctable_loopback(io::IOBlock &io, std::map<std::string, std::string> &cycle_row)
{
  if (cycle_row.empty())
  {
    io::LOG(io::DEBUG) << "engineCycle() SCTABLE END io.sctable.getFileLink() "
                       << io.sctable.getFileLink() << " io.sctable.getRowId() " << io.sctable.getRowId();

    io.sctable.init(io.sctable.getFileLink());
    cycle_row = io.sctable.getRowMap();
    if (cycle_row.empty())
    {
      io::LOG(io::ERROR) << "engineCycle() cycle_row.empty() corrupted file";
      return 1; // if wrong file, inhibit the engine
    }
  }

  //Check Eventual Errors
  //Check row id
  try
  {
    epicsUInt64 row_id = std::stoll(cycle_row["Id"]);
    if (row_id != io.sctable.getRowId())
      io::LOG(io::ERROR) << "engineCycle() io.sctable.getFileLink() " << io.sctable.getFileLink()
                         << " row_id!=io.sctable.getRowId() row_id " << row_id << " io.sctable.getRowId() " << io.sctable.getRowId();
  }
  catch (...)
  {
    io::LOG(io::ERROR) << "engineCycle() Id checkup failed at io.cId " << io.cId;
  }
  return 0;
}

int InhEvts4State(io::IOBlock &io, std::map<std::string, std::string> &cycle_row)
{
  for (auto &state : io.SCEConfig_yml.getInhStates())
    if (io.getPBState() == state)
      for (auto &it : io.SCEConfig_yml.getInhEvts())
        cycle_row.erase(it);

  return 0;
}

int engineCycle(io::IOBlock &io)
{
  // Performance improvement of the engineCycle()
  static std::map<std::string, std::string> cycle_row;
  static epicsUInt32 tst = 0; // The timestamp holder

  // Start the cycle
  // ===============
  io.cPeriod = cmn::period_us(tst);
  io.cId++;
  io::LOG(io::DEBUG) << "engineCycle() io.cPeriod " << io.cPeriod << " io.cId " << io.cId;
  // Get sctable row
  cycle_row = io.sctable.getRowMap();
  // Loop the supercycle table
  if (sctable_loopback(io, cycle_row) > 0)
    return 1;

  // Write other cycle variables
  std::map<std::string, std::string> cycle_row_adds = {};
  // cycle_row_adds[env::EVT2Str.at(env::COFFSET)] = cmn::str(io.cOffset);
  // Insert generated cycle variables into the cycle row
  cycle_row_insert(cycle_row, cycle_row_adds);

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
  cycle_row["PBState"] = io.SCEConfig_yml.SCESwitchBehaviour();
  if (cycle_row["PBState"].empty())
    cycle_row["PBState"] = io.getPBState();
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBState, io.DBuf_yml.PBStateIds_yml.getMap());
  // PBDest
  cycle_row["PBDest"] = io.getPBDest();
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBDest, io.DBuf_yml.PBDestIds_yml.getMap());
  // PBMod
  cycle_row["PBMod"] = io.getPBMod();
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBMod, io.DBuf_yml.PBModIds_yml.getMap());
  // PBLen
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBLen);
  // PBEn
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBEn);
  // PBCurr
  io_dbuf_safe_write(io.dbuf, cycle_row, env::PBCurr);

  // Erease inhibit events from the cycle in regards to the state
  InhEvts4State(io, cycle_row);
  // Update the event sequence container
  io.Seq.write(cycle_row);

  //Check the buffer
  io::LOG(io::DEBUG) << "engineCycle() io.SEQ.getSeq() "
                     << cmn::map2str<epicsUInt32, epicsUInt32>(io.Seq.getSeqMap())
                     << " io.dbuf.getDbuf() "
                     << cmn::map2str<epicsUInt32, epicsUInt32>(io.dbuf.getDbuf());

  return 0;
}
