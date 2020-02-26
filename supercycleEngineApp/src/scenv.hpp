
#ifndef SCENV_HPP_
#define SCENV_HPP_

#include <map>
#include <string>

namespace env
{

#define EPICS2020s 946708560
#define CYCLE_fHz 14
#define GETVARNAME(var) (#var)

enum EVT
{
    C14HZ = 0x0E,   // DOWNSTREAM START OF CYCLE
    COFFSET = 0x10, // DOWNSTREAM SEND COFFSET BUFFER
    CSYNC = 0x11,   // DOWNSTREAM Trigger the cycle within the supercycle APP
    SEQ_END = 127,  // DOWNSTREAM Trigger the cycle within the supercycle APP
};

//std::cout << " enum ProtoVer " << EVTS2Str.at(ProtoVer) << std::endl;
//const boost::unordered_map<EVT, std::string> EVT2Str =
//    boost::assign::map_list_of(C14HZ, "14HZ")(COFFSET, "COFFSET")(CSYNC, "CSYNC")(SEQ_END, "SEQ_END");
extern const std::map<EVT, std::string> EVT2Str;

enum DBFIDX
{
    ProtNum = 0,  //InitTable | PV-RB
    ProtVer = 2,  //InitTable | PV-RB
    IdCycle = 4,  //Cycle Callback Increment | PV-RB
    PBState = 12, //SCTable | PV-RB | PV-SP | EVG input?
    PBDest = 13,  //SCTable | PV-RB | PV-SP
    PBMod = 14,   //SCTable | PV-RB | PV-SP
    PBLen = 16,   //SCTable | PV-RB | PV-SP
    PBEn = 20,    //SCTable | PV-RB | PV-SP
    PBCurr = 24,  //SCTable | PV-RB | PV-SP
    TgRast = 28,  //SCTable | PV-RB | PV-SP
    TgSeg = 29,   //Upstream EVT_TGFM | PV-RB
};

extern const std::map<DBFIDX, std::string> DBFIDX2Str;
//#define GetDbfIdx2Str(idx) (env::DBFIDX2Str.at(env::idx))

//std::map<std::string, epicsUInt32> MEVTS = {{"EVT", 10}};

} // namespace env

#endif // SCENV_HPP_
