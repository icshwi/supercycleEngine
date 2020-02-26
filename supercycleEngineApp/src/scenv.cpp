#include "scenv.hpp"

namespace env
{

std::map<EVT, std::string> EVT2Str = {
    {C14HZ, "14HZ"},
    {COFFSET, "COFFSET"},
    {CSYNC, "CSYNC"},
    {SEQ_END, "SEQ_END"}};

std::map<DBFIDX, std::string> DBFIDX2Str = {
    {ProtNum, "ProtNum"},
    {ProtVer, "ProtVer"},
    {IdCycle, "IdCycle"},
    {PBState, "PBState"},
    {PBDest, "PBDest"},
    {PBMod, "PBMod"},
    {PBLen, "PBLen"},
    {PBEn, "PBEn"},
    {PBCurr, "PBCurr"},
    {TgRast, "TgRast"},
    {TgSeg, "TgSeg"}};

} // namespace env
