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

void cycle_row_insert(std::map<std::string, std::string> &rowm, std::map<std::string, std::string> argm)
{
    rowm.insert(argm.begin(), argm.end());
}

int sctable_loopback(io::IOBlock &io, std::map<std::string, std::string> &cycle_row)
{
    if (cycle_row.empty())
    {
        io::LOG(io::DEBUG) << "engineCycle() SCTABLE END io.sctable.getFileLink() " << io.sctable.getFileLink() << " io.sctable.getRowId() " << io.sctable.getRowId();
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
            io::LOG(io::ERROR) << "engineCycle() io.sctable.getFileLink() " << io.sctable.getFileLink() << " row_id!=io.sctable.getRowId() row_id " << row_id << " io.sctable.getRowId() " << io.sctable.getRowId();
    }
    catch (...)
    {
        io::LOG(io::ERROR) << "engineCycle() Id checkup failed at io.cId " << io.cId;
    }
    return 0;
}

int sctable_switch(io::IOBlock &io)
{
    if (io.get_sctable_csv_link().compare(io.sctable.getFileLink()) != 0)
    {
        io::LOG(io::DEBUG) << "engineCycle() different sctable selected OLD io.sctable.getFileLink() " << io.sctable.getFileLink() << " NEW io.get_sctable_csv_link() " << io.get_sctable_csv_link();
        io.sctable.init(io.get_sctable_csv_link());
    }
    return 0;
}

int engineCycle(io::IOBlock &io)
{
    // Performance improvement of the engineCycle()
    static std::map<std::string, std::string> cycle_row;
    static epicsUInt32 tst = 0; // The timestamp holder

    io::LOG(io::DEBUG1) << "engineCycle()";
    io.cPeriod = cmn::period_us(tst);
    io::LOG(io::DEBUG) << "engineCycle() io.cPeriod " << io.cPeriod;

    // Start the cycle
    // ===============
    io.cId++;
    // Change the table if requested
    sctable_switch(io);
    // Get sctable row
    cycle_row = io.sctable.getRowMap();
    // Loop the supercycle table
    if (sctable_loopback(io, cycle_row) > 0)
        return 1;

    // Write other cycle variables
    std::map<std::string, std::string> cycle_row_adds = {};
    cycle_row_adds[env::EVT2Str.at(env::DATA)] = cmn::str(io.cOffset);

    // Insert other cycle variables
    cycle_row_insert(cycle_row, cycle_row_adds);
    // Update the databuffer container

    io.dbuf.clear();
    // ProtNum
    io.dbuf.write(env::ProtNum, io.json_dbuf.ProtNum);
    // ProtVer
    io.dbuf.write(env::ProtVer, io.json_dbuf.ProtVer);
    // IdCycle
    io.dbuf.write(env::IdCycle, (epicsUInt32)io.cId);

    // SCTABLE operations
    // PBState
    io_dbuf_safe_write(io.dbuf, cycle_row, env::PBState, io.json_dbuf.PBState);
    // PBDest
    io_dbuf_safe_write(io.dbuf, cycle_row, env::PBDest, io.json_dbuf.PBDest);
    // PBMod
    io_dbuf_safe_write(io.dbuf, cycle_row, env::PBMod, io.json_dbuf.PBMod);
    // PBLen
    io_dbuf_safe_write(io.dbuf, cycle_row, env::PBLen);
    // PBEn
    io_dbuf_safe_write(io.dbuf, cycle_row, env::PBEn);
    // PBCurr
    io_dbuf_safe_write(io.dbuf, cycle_row, env::PBCurr);

    // Update the event sequence container
    io.SEQ.write(cycle_row);

    //Check the buffer
    io::LOG(io::DEBUG) << "engineCycle() cmn::map2str<epicsUInt32,epicsUInt32>(io.SEQ.getSeq()) " << cmn::map2str<epicsUInt32, epicsUInt32>(io.SEQ.getSeq());
    io::LOG(io::DEBUG) << "engineCycle() cmn::map2str<epicsUInt32,epicsUInt32>(io.dbuf.getDbuf()) " << cmn::map2str<epicsUInt32, epicsUInt32>(io.dbuf.getDbuf());

    return 0;
}
