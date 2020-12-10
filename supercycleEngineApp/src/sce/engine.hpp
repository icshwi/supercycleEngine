/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#pragma once

#include "ioblock.hpp"
#include "scenv.hpp"

#include <epicsTypes.h>

int databufferCycle(io::IOBlock& io, std::map<std::string, std::string>& cycle_row);
int sequenceCycle(sce::SequenceHandler& seq, const std::map<std::string, std::string>& cycle_row);
int statsCycle(io::IOBlock& io);
