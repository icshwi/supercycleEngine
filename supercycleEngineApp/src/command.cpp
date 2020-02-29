#include <iocsh.h>
#include <epicsExport.h>

#include <iostream>

/* vmecsrprint */
static const iocshArg Arg0 = {"filename ", iocshArgString};
static const iocshArg *const Args[1] = {&Arg0};
static const iocshFuncDef printFuncDef = {"testprint", 1, Args};

static void printCall(const iocshArgBuf *arg)
{
    std::cout << "printCall" << std::endl;
    std::cout << arg->sval << std::endl;
    //vmecsrprint(arg[0].ival,arg[1].ival);
}

static void csr(void)
{
    iocshRegister(&printFuncDef, printCall);
}
epicsExportRegistrar(csr);
