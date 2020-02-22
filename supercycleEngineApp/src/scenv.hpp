
#ifndef SCENV_HPP_
#define SCENV_HPP_

#include <map>
#include <string>
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>

namespace env
{

#define EPICS2020s 946708560
#define CYCLE_fHz 14

enum EVT
{
    C14HZ = 0x0E,  // DOWNSTREAM START OF CYCLE
    DATA = 0x10,   // DOWNSTREAM SEND DATA BUFFER
    DATAS = 0x11,  // DOWNSTREAM Trigger the cycle within the supercycle APP
    SEQ_END = 127, // DOWNSTREAM Trigger the cycle within the supercycle APP
};

//std::cout << " enum ProtoVer " << EVTS2Str.at(ProtoVer) << std::endl;
const boost::unordered_map<EVT, std::string> EVT2Str =
    boost::assign::map_list_of(C14HZ, "14HZ")(DATA, "DATA")(DATAS, "DATAS")(SEQ_END, "SEQ_END");

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

const boost::unordered_map<DBFIDX, std::string> DBFIDX2Str =
    boost::assign::map_list_of(ProtNum, "ProtNum")(ProtVer, "ProtVer")(IdCycle, "IdCycle")(PBState, "PBState")(PBDest, "PBDest")(PBMod, "PBMod")(PBLen, "PBLen")(PBEn, "PBEn")(PBCurr, "PBCurr")(TgRast, "TgRast")(TgSeg, "TgSeg"); //std::cout << " enum ProtoVer " << DBFIDX2Str.at(ProtoVer) << std::endl;

#define GetDbfIdx2Str(idx) (env::DBFIDX2Str.at(env::idx))

} // namespace env

#endif // SCENV_HPP_
