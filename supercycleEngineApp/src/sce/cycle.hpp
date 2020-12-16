/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#pragma once

#include <epicsTypes.h>

#include "memreg.hpp"
//#include "scenv.hpp"

namespace cycle
{
int databuffer(mem::ScERegistry& io, std::map<std::string, std::string>& cycle_row);
int sequence(const sce::SequenceHandler& seq, const std::map<std::string, std::string>& cycle_row);
int stats(const mem::ScERegistry& io);
} // namespace cycle
