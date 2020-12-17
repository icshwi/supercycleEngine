/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "scenv.hpp"

namespace env
{

// const std::map<EVT, std::string> EVT2Str = {
//     {C14Hz, "14Hz"},
//     {COffset, "COffset"},
//     {CSync, "CSync"},
//     {SeqEnd, "SeqEnd"}};

const std::map<DBFIDX, std::string> DBFIDX2Str = {
    {ProtNum, "ProtNum"},
    {ProtVer, "ProtVer"},
    {IdCycle, "IdCycle"},
    {PBState, "PBState"},
    {PBDest, "PBDest"},
    {PBMod, "PBMod"},
    {PBPresent, "PBPresent"},
    {PBLen, "PBLen"},
    {PBEn, "PBEn"},
    {PBCurr, "PBCurr"},
    {TgRast, "TgRast"},
    {TgSeg, "TgSeg"}};

} // namespace env
