/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#pragma once

#include <map>
#include <string>

namespace env
{

//#define EPICS2020s 946708560

enum EVT
{
  C14Hz = 0x0E,   // DOWNSTREAM START OF CYCLE
  COffset = 0x10, // DOWNSTREAM SEND COFFSET BUFFER
  CSync = 0x11,   // DOWNSTREAM Trigger the cycle within the supercycle APP
  SeqEnd = 127,   // DOWNSTREAM Trigger the cycle within the supercycle APP
};

enum DBFIDX
{
  ProtNum = 0,    //InitTable | PV-RB
  ProtVer = 2,    //InitTable | PV-RB
  IdCycle = 4,    //Cycle Callback Increment | PV-RB
  PBState = 12,   //SCTable | PV-RB | PV-SP | EVG input?
  PBDest = 13,    //SCTable | PV-RB | PV-SP
  PBMod = 14,     //SCTable | PV-RB | PV-SP
  PBPresent = 15, //SCTable | PV-RB | PV-SP
  PBLen = 16,     //SCTable | PV-RB | PV-SP
  PBEn = 20,      //SCTable | PV-RB | PV-SP
  PBCurr = 24,    //SCTable | PV-RB | PV-SP
  TgRast = 28,    //SCTable | PV-RB | PV-SP
  TgSeg = 29,     //Upstream EVT_TGFM | PV-RB
};

//extern const std::map<EVT, std::string> EVT2Str;
extern const std::map<DBFIDX, std::string> DBFIDX2Str;

} // namespace env
