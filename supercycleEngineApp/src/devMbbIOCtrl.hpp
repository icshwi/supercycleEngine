/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-10-28
 */

#ifndef DEVMBBIOCTRL_HPP_
#define DEVMBBIOCTRL_HPP_

#include <map>

#include <epicsTypes.h>

extern std::map<std::string, epicsUInt32> RegisteredMbboMap;

#endif // DEVMBBIOCTRL_HPP_
