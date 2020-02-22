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

epicsUInt32 epicssTstSysNowSec();
//epicsUInt32 wclock_s();
epicsUInt32 tst_ms();
epicsUInt32 tst_us();
epicsUInt32 tst_ns();
std::string epicssTstSysNow();
epicsUInt32 period_us(epicsUInt32 &argtst);
std::string str(int arg);
std::string str(std::string arg);
void gcc_info();
void gcc_assert(long ver = 201103L);

#include "cmnbase.tpp"

} // namespace cmn

#endif // CMNBASE_HPP
