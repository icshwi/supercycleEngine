/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#pragma once

#include <epicsTypes.h>

#include "ioblock.hpp"
//#include "scenv.hpp"

namespace cycle
{
int databuffer(io::IOBlock& io, std::map<std::string, std::string>& cycle_row);
int sequence(sce::SequenceHandler& seq, const std::map<std::string, std::string>& cycle_row);
int stats(io::IOBlock& io);
} // namespace cycle
