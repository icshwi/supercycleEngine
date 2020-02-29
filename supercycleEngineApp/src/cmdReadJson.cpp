#include "cmdReadJson.hpp"

#include <iocsh.h>
#include <epicsExport.h>

#include <iostream>
#include <fstream>

JsonRoot &RegisteredJsonRoot()
{
    static JsonRoot jr;
    return jr;
}

void JsonRoot::init(std::string fname)
{
    JsonRoot &jr = RegisteredJsonRoot();
    std::ifstream ifs = {};
    Json::Reader reader;
    Json::Value jval;
    bool state = false;

    ifs.open(fname, std::ifstream::in);
    state = reader.parse(ifs, jval);
    ifs.close();

    if (state == true)
    {
        jr.fnamev.push_back(fname);
        jr.rootv.push_back(jval);
        jr.keyv.push_back(jval.getMemberNames());
    }
}

static const iocshArg jsonArg0 = {"filename", iocshArgString};
static const iocshArg *const jsonArgs[1] = {&jsonArg0};
static const iocshFuncDef readJsonFuncDef = {"readJson", 1, jsonArgs};

static void readJsonCall(const iocshArgBuf *arg)
{
    JsonRoot &jr = RegisteredJsonRoot();

    jr.init(arg->sval);
}

static const iocshArg stringArg0 = {"key", iocshArgString};
static const iocshArg stringArg1 = {"val", iocshArgString};
static const iocshArg *const stringArgs[2] = {&stringArg0, &stringArg1};
static const iocshFuncDef readStringFuncDef = {"readStringMap", 2, stringArgs};

std::map<std::string, std::string> RegisteredStringM;

static void readStringMapCall(const iocshArgBuf *arg)
{
    RegisteredStringM[arg[0].sval] = arg[1].sval;
}

static void iocmd(void)
{
    iocshRegister(&readJsonFuncDef, readJsonCall);
    iocshRegister(&readStringFuncDef, readStringMapCall);
}
epicsExportRegistrar(iocmd);
