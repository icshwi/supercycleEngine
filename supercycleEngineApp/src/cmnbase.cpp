/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "cmnbase.hpp"

#include <sys/time.h>
#include <string>
#include <iostream> // std::cout, std::endl
#include <iomanip>  // std::setfill, std::setw
#include <sstream>
#include <map>
#include <vector>
#include <assert.h>
#include <chrono>
#include <fstream>
//#include <regex>

namespace cmn
{

bool isSubstring(std::string s, std::string subs)
{
    if (s.find(subs) != std::string::npos)
    {
        return true;
    }
    return false;
}

bool isFile(std::string fname)
{
    std::ifstream file(fname);
    if (!file)
        return false;

    return true;
}

std::string str(epicsUInt32 arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

std::string str(std::string arg)
{
    return arg;
}

std::string epicssTstSysNow()
{
    epicsTimeStamp ts;
    char ts_buf[100];

    epicsTimeGetCurrent(&ts);
    size_t r = epicsTimeToStrftime(ts_buf, sizeof(ts_buf), TSTFORMAT, &ts);

    if (r == 0)
        return {};

    std::string ts_str(ts_buf);

    return ts_str;
}

epicsUInt32 epicssTstSysNowSec()
{
    epicsTimeStamp ts;
    epicsTimeGetCurrent(&ts);
    return ts.secPastEpoch;
}

//epicsUInt32 wclock_s()
//{
//    return (epicsUInt32)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
//}

epicsUInt32 tst_ms()
{
    return (epicsUInt32)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

epicsUInt32 tst_us()
{
    return (epicsUInt32)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

epicsUInt32 period_us(epicsUInt32 &argtst)
{
    epicsUInt32 tst_us = (epicsUInt32)cmn::tst_us();
    epicsUInt32 p_us = tst_us - argtst;
    argtst = tst_us;
    return p_us;
}

void gcc_info()
{
    if (__cplusplus == 201703L)
        std::cout << "C++17\n";
    else if (__cplusplus == 201402L)
        std::cout << "C++14\n";
    else if (__cplusplus == 201103L)
        std::cout << "C++11\n";
    else if (__cplusplus == 199711L)
        std::cout << "C++98\n";
    else
        std::cout << "pre-standard C++\n";

    std::cout << "__cplusplus " << __cplusplus << std::endl;
    //std::cout << "__STDC_VERSION__ " << __STDC_VERSION__ << std::endl;
    std::cout << "__STDC__ " << __STDC__ << std::endl;
    std::cout << "__STDC_HOSTED__ " << __STDC_HOSTED__ << std::endl;
    std::cout << "__FILE__ " << __FILE__ << std::endl;
}

void gcc_assert(long ver)
{
    assert((ver >= __cplusplus) && "The gcc version is too old.");
}

} // namespace cmn
