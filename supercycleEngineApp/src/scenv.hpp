/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef SCENV_HPP_
#define SCENV_HPP_

#include <map>
#include <string>

namespace env
{

#define EPICS2020s 946708560
#define GETVARNAME(var) (#var)

enum EVT
{
    C14HZ = 0x0E,   // DOWNSTREAM START OF CYCLE
    COFFSET = 0x10, // DOWNSTREAM SEND COFFSET BUFFER
    CSYNC = 0x11,   // DOWNSTREAM Trigger the cycle within the supercycle APP
    SEQ_END = 127,  // DOWNSTREAM Trigger the cycle within the supercycle APP
};

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

} // namespace env

#endif // SCENV_HPP_
