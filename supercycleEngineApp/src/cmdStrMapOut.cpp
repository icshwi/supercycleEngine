#include "cmdStrMapOut.hpp"

#include <iocsh.h>
#include <epicsExport.h>

static const iocshArg strArg0 = {"key", iocshArgString};
static const iocshArg strArg1 = {"val", iocshArgString};
static const iocshArg *const strArgs[2] = {&strArg0, &strArg1};
static const iocshFuncDef strMapOutFuncDef = {"strMapOut", 2, strArgs};

std::map<std::string, std::string> RegisteredStringMap;

static void strMapOutCall(const iocshArgBuf *arg)
{
    RegisteredStringMap[arg[0].sval] = arg[1].sval;
}

static void cmdStrMapOut(void)
{
    iocshRegister(&strMapOutFuncDef, strMapOutCall);
}
epicsExportRegistrar(cmdStrMapOut);
