/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-15
 */

#pragma once

#include "cmdMapStrOut.hpp"
#include "devStringoutCtrl.hpp"
#include <string>

namespace devio
{

std::string getDbufCfgPath() { return devreg::CmdMapStrOut()["DBufCfgPath"]; };
std::string getMEvtsCfgPath() { return devreg::CmdMapStrOut()["MEvtsCfgPath"]; };
std::string getScECfgPath() { return devreg::CmdMapStrOut()["ScECfgPath"]; };
//std::string getDbufCfgPath() { return MAPSTROUT["DBufCfgPath"]; };

} // namespace devio
