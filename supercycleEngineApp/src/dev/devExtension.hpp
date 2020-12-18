/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#pragma once

#include <devSup.h>
#include <string>

extern "C"
{
  struct CmnDset
  {
    long num; // space for 6 functions
    DEVSUPFUN report;
    DEVSUPFUN init;
    DEVSUPFUN init_record;
    DEVSUPFUN get_ioint_info;
    DEVSUPFUN io;
    DEVSUPFUN special_linconv;
  };
  typedef struct CmnDset CmnDset;
}

#define CMNDSET(obj)                    \
  static CmnDset dev##obj = {           \
      6, NULL, NULL,                    \
      (DEVSUPFUN)init_record_##obj,     \
      NULL,                             \
      (DEVSUPFUN)read_string_##obj,     \
      NULL};                            \
  extern "C"                            \
  {                                     \
    epicsExportAddress(dset, dev##obj); \
  }

// struct DevPriv
// {
//   unsigned int seed;
// };

namespace dev
{

std::string db_inp_val(std::string args, std::string key);

} // namespace dev
