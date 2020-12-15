/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-15
 */

#include "devIO.hpp"
#include <string>

#define FBody_CmdMapStrOut(obj) \
  std::string get##obj() { return devreg::CmdMapStrOut().at(#obj); }

#define FBody_StrOutCtrlMap(obj) \
  std::string get##obj() { return devreg::StrOutCtrlMap()[devio::getPrefix() + #obj + "-SP"]; }

namespace devio
{
FBody_CmdMapStrOut(DBufCfgPath);
FBody_CmdMapStrOut(MEvtsCfgPath);
FBody_CmdMapStrOut(ScECfgPath);
FBody_CmdMapStrOut(Prefix);
FBody_CmdMapStrOut(ScTableDir);

FBody_StrOutCtrlMap(ScTable);
FBody_StrOutCtrlMap(PBState);
FBody_StrOutCtrlMap(PBMod);
FBody_StrOutCtrlMap(PBDest);

//Complex functions
std::string getScTablePath() { return (devio::getScTableDir() + devio::getScTable()); };
} // namespace devio
