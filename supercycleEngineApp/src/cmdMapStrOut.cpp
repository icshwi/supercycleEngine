#include "cmdMapStrOut.hpp"

#include <iocsh.h>
#include <epicsExport.h>

static const iocshArg strArg0 = {"key", iocshArgString};
static const iocshArg strArg1 = {"val", iocshArgString};
static const iocshArg *const strArgs[2] = {&strArg0, &strArg1};
static const iocshFuncDef mapStrOutFuncDef = {"mapStrOut", 2, strArgs};

std::map<std::string, std::string> RegisteredCmdMapStrOut;

static void mapStrOutCall(const iocshArgBuf *arg)
{
    RegisteredCmdMapStrOut[arg[0].sval] = arg[1].sval;
}

static void cmdMapStrOut(void)
{
    iocshRegister(&mapStrOutFuncDef, mapStrOutCall);
}
epicsExportRegistrar(cmdMapStrOut);
