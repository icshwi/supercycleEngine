/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <epicsTime.h>
#include <epicsTypes.h>
//Common Libraries Namespace

#define TSTFORMAT "%Y-%m-%dT%H:%M:%S.%06f"
#define __COMPACT_PRETTY_FUNCTION__ cmn::compiler::funcName(__FUNCTION__, __PRETTY_FUNCTION__)
namespace cmn
{
namespace compiler
{
std::string info();
void assure(long ver = 201103L);
std::string funcName(const std::string& function, const std::string& prettyFunction);
} // namespace compiler

namespace file
{
bool exists(std::string fname);
} // namespace file

namespace tst
{
epicsUInt32 sec_now();
std::string epics_now();
//epicsUInt32 wclock_s();
epicsUInt32 ms_now();
epicsUInt32 us_now();
//epicsUInt32 ns();
epicsUInt32 period_us(epicsUInt32& argtst);
} // namespace tst

namespace str
{
std::vector<std::string> split(const std::string&, char c = ',');
std::string remove(const std::string& args, char c = ' ');
std::string convert(epicsUInt32);
std::string convert(std::string);
void replace(std::string&, char c_old, char c_new);
void erase(std::string&, char);
} // namespace str

} // namespace cmn

#include "cmnbase.tpp"
