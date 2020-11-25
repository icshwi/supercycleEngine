/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef CMNBASE_HPP_
#define CMNBASE_HPP_

#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include <epicsTypes.h>
#include <epicsTime.h>
//Common Libraries Namespace

#define TSTFORMAT "%Y-%m-%dT%H:%M:%S.%06f"

namespace cmn
{

bool isSubstring(std::string s, std::string subs);
bool isFile(std::string fname);
std::string str(epicsUInt32 arg);
std::string str(std::string arg);
epicsUInt32 epicssTstSysNowSec();
//epicsUInt32 wclock_s();
epicsUInt32 tst_ms();
epicsUInt32 tst_us();
epicsUInt32 tst_ns();
std::string epicssTstSysNow();
epicsUInt32 period_us(epicsUInt32 &argtst);
void gcc_info();
void gcc_assert(long ver = 201103L);

} // namespace cmn

#include "cmnbase.tpp"

#endif // CMNBASE_HPP
