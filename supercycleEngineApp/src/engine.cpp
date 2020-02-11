#include "engine.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

// Epics
#include "cadef.h"
#include "dbDefs.h"
#include "epicsString.h"
#include "cantProceed.h"

//#include "cacallback.hpp"
#include "dbuf.hpp"
#include "csv.hpp"
#include "json.hpp"

//#include <unistd.h>

//using namespace dbf;
//using namespace env;

// Local variables
// condition_variable::notify_one
// #include <thread>          // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
std::mutex mtx;
std::condition_variable cycle_cv;
//Cycle inhibit
int cycle_flag = 0;     // shared value by the engine

uint64_t cycle_id=(cmn::wclock_s()-YEAR2020s)*CYCLE_fHz;
uint64_t cycle_spark=cycle_id;

void
engineCbSpark(struct event_handler_args eha)
{
    io::LOG(io::DEBUG2) << "engineCbSpark()";
    if (cycle_flag == 1) io::LOG(io::ERROR) << "engineCbSpark() Engine Cycle Not Synchronized, cycle_flag " << cycle_flag;
    else io::LOG(io::DEBUG1) << "engineCbSpark() Engine Cycle Synchronized, cycle_flag " << cycle_flag;

    //eha.dbr returns string form CA
    //char *pdata = (char *)eha.dbr;
    //io.datapacket.data[IdCycle] = (uint32_t) atol(pdata);

    io::LOG(io::DEBUG1) << "engineCbSpark cycle_spark " << cycle_spark << " cycle_id " << cycle_id;
    if (cycle_spark != cycle_id)
    {
        io::LOG(io::ERROR) << "engineCbSpark() engineCycle() lost cycles " << (cycle_spark-cycle_id);
        cycle_spark = cycle_id;
    }

    cycle_spark++;
    //End the callback and notify the engine
    cycle_flag = 1;
    cycle_cv.notify_one();
}

void
engineCycleWait()
{
    io::LOG(io::DEBUG1) << "engineCycleWait()";
    std::unique_lock<std::mutex> lck(mtx);
    //while (cycle_flag==0) cycle_cv.wait(lck);
    cycle_cv.wait(lck);
    cycle_flag = 0;
    io::LOG(io::DEBUG1) << "engineCycleWait() END";
}

// Engine Main
// Helpers
//#define io_json_keyid_get(key) io.initjson.key[scrow[GetDbfIdx2Str(key)]]["id"].asUInt()
//#define io_scrow_val_get(key) std::stol(scrow[GetDbfIdx2Str(key)])

void
io_dbuf_safe_write(dbf::DBufPacket &dbuf, std::map<std::string, std::string> &row, env::DBFIDX idx)
{
    try {
        dbuf.write(idx,std::stol(row[env::DBFIDX2Str.at(idx)]));
    } catch(...) {
        dbuf.write(idx,0);  // Worse case selected so that the beam is on
        io::LOG(io::WARNING) << "writeDbufSafe() idx not defined!, env::DBFIDX2Str.at(idx) "<< env::DBFIDX2Str.at(idx);
    }
}

void
io_dbuf_safe_write(dbf::DBufPacket &dbuf, std::map<std::string, std::string> &row, env::DBFIDX idx, const Json::Value & jsonv)
{
    try {
        dbuf.write(idx,jsonv[row[env::DBFIDX2Str.at(idx)]]["id"].asUInt());
    } catch(...) {
        dbuf.write(idx,0);  // Worse case selected so that the beam is on
        io::LOG(io::WARNING) << "writeDbufSafe() idx not defined!, env::DBFIDX2Str.at(idx) "<< env::DBFIDX2Str.at(idx);
    }
}

int
engineCycle(io::IOBlock &io)
{
    // Performance improvement of the engineCycle()
    static std::map<std::string, std::string> scrow;
    static uint tst=0; // The timestamp holder

    io::LOG(io::DEBUG1) << "engineCycle()";
    uint sc_prd_us = cmn::period_us(tst);
    io::LOG(io::DEBUG) << "engineCycle() sc_prd_us " << sc_prd_us;

    // Engine Maintenance
    if ( io.get_sctable_csv_link().compare(io.sctable.getFileLink()) !=0 )
    {
        io::LOG(io::DEBUG) << "engineCycle() different sctable selected OLD io.sctable.getFileLink() " << io.sctable.getFileLink() << " NEW io.get_sctable_csv_link() " << io.get_sctable_csv_link();
        io.sctable.init(io.get_sctable_csv_link());
    }

    // Get sctable row
    cycle_id++;
    scrow = io.sctable.getRowMap();
    // Loop the supercycle table
    if(scrow.empty())
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
    try {
        uint64_t row_id = std::stol(scrow["Id"]);
        if ( row_id != io.sctable.getRowId() )
            io::LOG(io::ERROR) << "engineCycle() io.sctable.getFileLink() " << io.sctable.getFileLink() << " row_id!=io.sctable.getRowId() row_id " << row_id << " io.sctable.getRowId() " << io.sctable.getRowId();
    } catch(...) {
        io::LOG(io::ERROR) << "engineCycle() Id checkup failed at cycle_id "<< cycle_id;
    }
    // Start the cycle
    // ===============

    // Update the databuffer container

    io.dbuf.clear();
     // ProtNum
    io.dbuf.write(env::ProtNum,io.json_dbuf.ProtNum);
     // ProtVer
    io.dbuf.write(env::ProtVer,io.json_dbuf.ProtVer);
     // IdCycle
    io.dbuf.write(env::IdCycle,(uint32_t)cycle_id);

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
    //io.SEQ.update(scrow);

    // GET Section - updates containers as well
    //uint arg_tmp=0; // support variable
     // TgRast
    //io.dbuf.write(env::TgRast,  io.TgRastCa.get(arg_tmp));
     // TgSeg
    //io.dbuf.write(env::TgSeg,   io.TgSegCa.get(arg_tmp));
     //update file for the nest cycle
    //io.SCTableCa.get(io.sctable_csv);

    // PUT Section - has to be last
     // Databuffer Send
    //io.DbusSendCa.put_vec(io.dbuf.vallist());     //Send the data buffer via the timing network
     // Sequence Send
    //io.SEQ.put();
     // Other PVs
     // IdCycle Send
    //io.IdCycleCa.put(io.dbuf.read(env::IdCycle));
    //io.PeriodCa.put(sc_prd_us);

    usleep(5);     //Assure that data is in EVRs

    // io.SoftEvtCa.put(env::DATAS);

    //Check the buffer
    //io::LOG(io::DEBUG) << "engineCycle() cmn::map2str<uint,uint>(io.SEQ.evttstbuf) " << cmn::map2str<uint,uint>(io.SEQ.getEvtTstSeq());
    io::LOG(io::DEBUG) << "engineCycle() cmn::map2str<uint,uint>(io.dbuf.getDbuf()) " << cmn::map2str<uint,uint>(io.dbuf.getDbuf());

    //std::string tmp;
    //io.RefTabsTopCa.get(tmp);
    //io::LOG(io::DEBUG) << "engineCycle() io.RefTabsTopCa.get(tmp) " << tmp;

    usleep(io.get_ECInhibit());

    return 0;
}
