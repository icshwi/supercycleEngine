/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "cmdMapStrOut.hpp"

#include <epicsExport.h>
#include <iocsh.h>

namespace devreg
{
std::map<std::string, std::string>& CmdMapStrOut()
{
  static std::map<std::string, std::string> reg_;
  return reg_;
}
} // namespace devreg

static const iocshArg strArg0 = {"key", iocshArgString};
static const iocshArg strArg1 = {"val", iocshArgString};
static const iocshArg* const strArgs[2] = {&strArg0, &strArg1};
static const iocshFuncDef mapStrOutFuncDef = {"mapStrOut", 2, strArgs};

static void mapStrOutCall(const iocshArgBuf* arg)
{
  devreg::CmdMapStrOut()[arg[0].sval] = arg[1].sval;
}

static void cmdMapStrOut(void)
{
  iocshRegister(&mapStrOutFuncDef, mapStrOutCall);
}

extern "C"
{
  epicsExportRegistrar(cmdMapStrOut);
}
