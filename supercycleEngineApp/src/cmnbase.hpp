#ifndef CMNBASE_HPP_
#define CMNBASE_HPP_

#include <map>
#include <vector>
#include <string>
#include <jsoncpp/json/json.h>
#include <algorithm>

#include <epicsTypes.h>
#include <epicsTime.h>
//Common Libraries Namespace
namespace cmn
{
bool substring(std::string s, std::string subs);
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
