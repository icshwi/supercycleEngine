#ifndef CMNBASE_HPP_
#define CMNBASE_HPP_

#include <map>
#include <vector>
#include <string>
#include <jsoncpp/json/json.h>
#include <algorithm>

#include <epicsTypes.h>
//Common Libraries Namespace
namespace cmn
{

std::string timestamp();
epicsUInt64 wclock_s();
epicsUInt64 tst_ms();
epicsUInt64 tst_us();
epicsUInt32 period_us(epicsUInt32 &argtst);
std::string str(int arg);
std::string str(std::string arg);
void gcc_info();
void gcc_assert(long ver = 201103L);

#include "cmnbase.tpp"

} // namespace cmn

#endif // CMNBASE_HPP
