#include <iocsh.h>
#include <epicsExport.h>

#include <iostream>

/* vmecsrprint */
static const iocshArg jsonArg0 = {"filename", iocshArgString};
static const iocshArg *const jsonArgs[1] = {&jsonArg0};
static const iocshFuncDef printFuncDef = {"readJson", 1, jsonArgs};

static void readJson(const iocshArgBuf *arg)
{
    std::cout << "readJson" << std::endl;
    std::cout << arg->sval << std::endl;
    //vmecsrprint(arg[0].ival,arg[1].ival);
}

static void jsoncmd(void)
{
    iocshRegister(&printFuncDef, readJson);
}
epicsExportRegistrar(jsoncmd);
