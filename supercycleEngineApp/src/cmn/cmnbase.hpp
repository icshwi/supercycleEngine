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
  void gcc_info();
  void gcc_assert(long ver = 201103L);

  bool isSubstring(std::string s, std::string subs);
  bool isFile(std::string fname);

  namespace tst
  {
    epicsUInt32 sec_now();
    std::string epics_now();
    //epicsUInt32 wclock_s();
    epicsUInt32 ms_now();
    epicsUInt32 us_now();
    //epicsUInt32 ns();
    epicsUInt32 period_us(epicsUInt32 &argtst);
  } // namespace tst

  namespace str
  {
    std::vector<std::string> split(std::string args, char c = ',');
    std::string remove(std::string args, char c = ' ');
    std::string convert(epicsUInt32 arg);
    std::string convert(std::string arg);
    std::vector<std::string> vect(const std::string&, char delim = ',');
  } // namespace str

} // namespace cmn

#include "cmnbase.tpp"

#endif // CMNBASE_HPP
