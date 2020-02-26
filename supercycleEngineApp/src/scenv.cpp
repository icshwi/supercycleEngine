#include "scenv.hpp"

namespace env
{

const boost::unordered_map<EVT, std::string> EVT2Str =
    boost::assign::map_list_of(C14HZ, "14HZ")(COFFSET, "COFFSET")(CSYNC, "CSYNC")(SEQ_END, "SEQ_END");

const boost::unordered_map<DBFIDX, std::string> DBFIDX2Str =
    boost::assign::map_list_of(ProtNum, "ProtNum")(ProtVer, "ProtVer")(IdCycle, "IdCycle")(PBState, "PBState")(PBDest, "PBDest")(PBMod, "PBMod")(PBLen, "PBLen")(PBEn, "PBEn")(PBCurr, "PBCurr")(TgRast, "TgRast")(TgSeg, "TgSeg"); //std::cout << " enum ProtoVer " << DBFIDX2Str.at(ProtoVer) << std::endl;

} // namespace env
