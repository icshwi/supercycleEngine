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
    timestamp += cmn::str(uint(tp.tv_usec));

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
int64_t wclock_s()
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

int64_t tst_ms()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

int64_t tst_us()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

uint period_us(uint &argtst)
{
    uint tst_us = (uint)cmn::tst_us();
    uint p_us = tst_us - argtst;
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

std::string getDictSafe(std::map<std::string, std::string> dict_arg, std::string arg)
{
    std::string str_tmp = "";

    str_tmp = dict_arg[arg];

    if (str_tmp.empty())
        return "NULL";
    //cmn::LOG(cmn::DEBUG) << "engineCycle";
    return str_tmp;
}

void vec2stdio(std::vector<uint> arg_v)
{
    std::vector<uint>::iterator i;

    for (i = arg_v.begin(); i != arg_v.end(); ++i)
        std::cout << *i << ' ';

    std::cout << std::endl;
}

int printVec(std::vector<std::string> vec)
{
    if (vec.empty())
    {
        std::cout << "Vector Empty" << std::endl;
        return -1;
    }

    for (std::string data : vec)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    return 0;
}

std::map<std::string, std::string> cli2map(int argc, char **argv, std::vector<std::string> keys)
{
    std::map<std::string, std::string> argv_map;
    argv_map["argv0"] = argv[0]; //always reference to the executed file

    for (int i = 1; i < argc; ++i)
    {
        for (auto const &key : keys)
        {
            if (key.compare(argv[i]) == 0)
                argv_map[key] = argv[i + 1];
        }
    }

    return argv_map;
}

void getMapVal(std::string &out, std::string key, std::map<std::string, std::string> argm)
{
    if (argm[key].empty() == false)
        out = argm[key];
}

std::string
getSafeMapVal(std::map<std::string, std::string> argm, std::string key)
{
    std::string tmps;
    try
    {
        tmps = argm[key];
        if (tmps.empty() == false)
            return tmps;
    }
    catch (...)
    {
        std::cout << "getSafeMapVal() key does not exist, key " << key << std::endl;
        //io::LOG(io::ERROR) << "checkMap() argm[key] does not exist, key " << key;
    }
    return tmps;
}

void json2map(Json::Value &argjval, std::map<std::string, std::string> &argm, std::string key)
{
    std::vector<std::string> tmpv = argjval.getMemberNames();

    for (auto const &it : tmpv)
    {
        argm[it] = argjval[it].get(key, "").asString();
    }
}

void json2map(Json::Value &argjval, std::map<std::string, uint> &argm, std::string key)
{
    std::vector<std::string> tmpv = argjval.getMemberNames();

    for (auto const &it : tmpv)
    {
        argm[it] = argjval[it].get(key, "").asUInt();
    }
}

} // namespace cmn
