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
  namespace compiler
  {
    std::string info()
    {
      std::string info_;

      if (__cplusplus == 201703L)
        info_.append("C++17 ");
      else if (__cplusplus == 201402L)
        info_.append("C++14 ");
      else if (__cplusplus == 201103L)
        info_.append("C++11 ");
      else if (__cplusplus == 199711L)
        info_.append("C++98 ");
      else
        info_.append("pre-standard C++ ");

      info_.append(" __cplusplus ");
      info_.append(cmn::str::convert(__cplusplus));
      //info_.append(" __STDC_VERSION__ ");
      //info_.append(cmn::str::convert(__STDC_VERSION__));
      info_.append(" __STDC__ ");
      info_.append(cmn::str::convert(__STDC__));
      info_.append(" __STDC_HOSTED__ ");
      info_.append(cmn::str::convert(__STDC_HOSTED__));
      //info_.append(" __FILE__ ");
      //info_.append(cmn::str::convert(__FILE__));
      return info_;
    }

    void assure(long ver)
    {
      assert((ver >= __cplusplus) && "The gcc version is too old.");
    }
  } // namespace compiler

  namespace file
  {
    bool exists(std::string fname)
    {
      std::ifstream file(fname);
      if (!file)
        return false;

      return true;
    }
  } // namespace file

  namespace tst
  {
    std::string epics_now()
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

    epicsUInt32 sec_now()
    {
      epicsTimeStamp ts;
      epicsTimeGetCurrent(&ts);
      return ts.secPastEpoch;
    }

    //epicsUInt32 wclock_s()
    //{
    //    return (epicsUInt32)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    //}

    epicsUInt32 ms_now()
    {
      return (epicsUInt32)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    epicsUInt32 us_now()
    {
      return (epicsUInt32)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    epicsUInt32 period_us(epicsUInt32 &argtst)
    {
      epicsUInt32 tst_us = (epicsUInt32)cmn::tst::us_now();
      epicsUInt32 p_us = tst_us - argtst;
      argtst = tst_us;
      return p_us;
    }
  } // namespace tst

  namespace str
  {
    std::string remove(std::string args, char c)
    {
      std::string rets = args;
      std::string::iterator end_pos = std::remove(rets.begin(), rets.end(), c);
      rets.erase(end_pos, rets.end());

      return rets;
    }

    std::vector<std::string> split(std::string args, char c)
    {
      std::string ins = cmn::str::remove(args, ' ');

      std::stringstream inss(ins);
      std::vector<std::string> result;
      std::string substr;

      while (inss.good())
      {
        getline(inss, substr, c);
        result.push_back(substr);
      }
      return result;
    }

    std::string convert(epicsUInt32 arg)
    {
      std::stringstream ss;
      ss << arg;
      return ss.str();
    }

    std::string convert(std::string arg)
    {
      return arg;
    }

    std::vector<std::string> vect(const std::string &line, char delim)
    {
      std::vector<std::string> outv;
      std::string tmp;
      std::stringstream ss(line);

      while (std::getline(ss, tmp, delim))
        outv.push_back(tmp);

      return outv;
    }

  } // namespace str

} // namespace cmn
