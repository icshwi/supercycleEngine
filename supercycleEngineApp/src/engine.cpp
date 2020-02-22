#include "engine.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

#include "dbuf.hpp"
#include "csv.hpp"
#include "json.hpp"
#include "seq.hpp"

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

void io_dbuf_safe_write(dbf::DBufPacket &dbuf, std::map<std::string, std::string> &row, env::DBFIDX idx, const Json::Value &jsonv)
{
    try
    {
        dbuf.write(idx, jsonv[row[env::DBFIDX2Str.at(idx)]]["id"].asUInt());
    }
    catch (...)
    {
        dbuf.write(idx, 0); // Worse case selected so that the beam is on
        io::LOG(io::WARNING) << "writeDbufSafe() idx not defined!, env::DBFIDX2Str.at(idx) " << env::DBFIDX2Str.at(idx);
    }
}

epicsUInt64 engineCycle(io::IOBlock &io)
{
    // Performance improvement of the engineCycle()
    static epicsUInt64 cycle_id = (cmn::epicssTstSysNowSec() - EPICS2020s) * CYCLE_fHz;
    static std::map<std::string, std::string> scrow;
    static epicsUInt32 tst = 0; // The timestamp holder

    io::LOG(io::DEBUG1) << "engineCycle()";
    io.sc_prd_us = cmn::period_us(tst);
    io::LOG(io::DEBUG) << "engineCycle() io.sc_prd_us " << io.sc_prd_us;

    // Engine Maintenance
    if (io.get_sctable_csv_link().compare(io.sctable.getFileLink()) != 0)
    {
        io::LOG(io::DEBUG) << "engineCycle() different sctable selected OLD io.sctable.getFileLink() " << io.sctable.getFileLink() << " NEW io.get_sctable_csv_link() " << io.get_sctable_csv_link();
        io.sctable.init(io.get_sctable_csv_link());
    }

    // Get sctable row
    cycle_id++;
    scrow = io.sctable.getRowMap();
    // Loop the supercycle table
    if (scrow.empty())
    {
        io::LOG(io::DEBUG) << "engineCycle() SCTABLE END io.sctable.getFileLink() " << io.sctable.getFileLink() << " io.sctable.getRowId() " << io.sctable.getRowId();
        io.sctable.init(io.sctable.getFileLink());
        scrow = io.sctable.getRowMap();
        if (scrow.empty())
        {
            io::LOG(io::ERROR) << "engineCycle() scrow.empty() corrupted file";
            return 1; // if wrong file, inhibit the engine
        }
    }

    //Check Eventual Errors
    //Check row id
    try
    {
        epicsUInt64 row_id = std::stoll(scrow["Id"]);
        if (row_id != io.sctable.getRowId())
            io::LOG(io::ERROR) << "engineCycle() io.sctable.getFileLink() " << io.sctable.getFileLink() << " row_id!=io.sctable.getRowId() row_id " << row_id << " io.sctable.getRowId() " << io.sctable.getRowId();
    }
    catch (...)
    {
        io::LOG(io::ERROR) << "engineCycle() Id checkup failed at cycle_id " << cycle_id;
    }
    // Start the cycle
    // ===============

    // Update the databuffer container

    io.dbuf.clear();
    // ProtNum
    io.dbuf.write(env::ProtNum, io.json_dbuf.ProtNum);
    // ProtVer
    io.dbuf.write(env::ProtVer, io.json_dbuf.ProtVer);
    // IdCycle
    io.dbuf.write(env::IdCycle, (epicsUInt32)cycle_id);

    // SCTABLE operations
    // PBState
    io_dbuf_safe_write(io.dbuf, scrow, env::PBState, io.json_dbuf.PBState);
    // PBDest
    io_dbuf_safe_write(io.dbuf, scrow, env::PBDest, io.json_dbuf.PBDest);
    // PBMod
    io_dbuf_safe_write(io.dbuf, scrow, env::PBMod, io.json_dbuf.PBMod);
    // PBLen
    io_dbuf_safe_write(io.dbuf, scrow, env::PBLen);
    // PBEn
    io_dbuf_safe_write(io.dbuf, scrow, env::PBEn);
    // PBCurr
    io_dbuf_safe_write(io.dbuf, scrow, env::PBCurr);

    // Update the event sequence container
    io.SEQ.write(scrow);

    //Check the buffer
    io::LOG(io::DEBUG) << "engineCycle() cmn::map2str<epicsUInt32,epicsUInt32>(io.SEQ.getSeq()) " << cmn::map2str<epicsUInt32, epicsUInt32>(io.SEQ.getSeq());
    io::LOG(io::DEBUG) << "engineCycle() cmn::map2str<epicsUInt32,epicsUInt32>(io.dbuf.getDbuf()) " << cmn::map2str<epicsUInt32, epicsUInt32>(io.dbuf.getDbuf());

    return cycle_id;
}
