#include "cmnbase.hpp"

#include <sys/time.h>
#include <string>
#include <iostream> // std::cout, std::endl
#include <iomanip>  // std::setfill, std::setw
#include <sstream>
#include <map>
#include <vector>
#include <assert.h>
//#include <boost/algorithm/string.hpp>
#include <chrono>

//#include <ctime>

namespace cmn
{

std::string str(int arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

std::string str(std::string arg)
{
    return arg;
}

std::string timestamp()
{
    std::string timestamp;
    time_t curr_time;
    tm *curr_tm;
    char time_str[100];
    struct timeval tp;
    gettimeofday(&tp, NULL);

    time(&curr_time);
    curr_tm = localtime(&curr_time);
    strftime(time_str, 50, "%FT%T", curr_tm);
    timestamp = time_str;
    timestamp += '.';
    timestamp += cmn::str(epicsUInt32(tp.tv_usec));

    return timestamp;
}

/*
int64_t tst_s()
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
*/

/*
* Timestamp in seconds from epoc
*/
epicsUInt64 wclock_s()
{
    return (epicsUInt64)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

epicsUInt64 tst_ms()
{
    return (epicsUInt64)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

epicsUInt64 tst_us()
{
    return (epicsUInt64)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
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
