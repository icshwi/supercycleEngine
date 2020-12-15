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

std::string getDbufCfgPath();
std::string getMEvtsCfgPath();
std::string getScECfgPath();

std::string getScTable();
std::string getPBState();
std::string getPBMod();
std::string getPBDest();

std::string getScTablePath();

} // namespace devio
