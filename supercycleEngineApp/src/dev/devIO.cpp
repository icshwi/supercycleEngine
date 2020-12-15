/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-15
 */

#include "devIO.hpp"
#include <string>

namespace devio
{
std::string getDbufCfgPath() { return devreg::CmdMapStrOut()["DBufCfgPath"]; };
std::string getMEvtsCfgPath() { return devreg::CmdMapStrOut()["MEvtsCfgPath"]; };
std::string getScECfgPath() { return devreg::CmdMapStrOut()["ScECfgPath"]; };
std::string getPrefix() { return devreg::CmdMapStrOut()["Prefix"]; };

std::string getScTable() { return devreg::StrOutCtrlMap()[getPrefix() + "ScTable-SP"]; };
std::string getPBState() { return devreg::StrOutCtrlMap()[getPrefix() + "PBState-SP"]; };
std::string getPBMod() { return devreg::StrOutCtrlMap()[getPrefix() + "PBMod-SP"]; };
std::string getPBDest() { return devreg::StrOutCtrlMap()[getPrefix() + "PBDest-SP"]; };

std::string getScTablePath() { return (devreg::CmdMapStrOut()["ScTableDir"] + devio::getScTable()); };
} // namespace devio
