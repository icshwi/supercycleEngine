/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "scenv.hpp"
#include "ioblock.hpp"

#include <epicsTypes.h>

int engineCycle(io::IOBlock &io);

#endif // ENGINE_HPP
