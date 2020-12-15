/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-15
 */

#pragma once

#include "cmdMapStrOut.hpp"
#include "devStringoutCtrl.hpp"

#include <string>

#include "scenv.hpp"

#define FHead_(obj) std::string get##obj()
namespace devio
{

FHead_(DBufCfgPath);
FHead_(MEvtsCfgPath);
FHead_(ScECfgPath);

FHead_(ScTable);
FHead_(PBState);
FHead_(PBMod);
FHead_(PBDest);

FHead_(ScTablePath);

} // namespace devio
