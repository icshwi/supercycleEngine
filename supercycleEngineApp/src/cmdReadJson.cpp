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

static const iocshArg stringArg0 = {"string", iocshArgString};
static const iocshArg *const stringArgs[1] = {&stringArg0};
static const iocshFuncDef readStringFuncDef = {"readString", 1, stringArgs};

std::vector<std::string> RegisteredStringV;

static void readStringCall(const iocshArgBuf *arg)
{
    RegisteredStringV.push_back(arg->sval);
    std::cout << arg->sval << std::endl;
}

static void iocmd(void)
{
    iocshRegister(&readJsonFuncDef, readJsonCall);
    iocshRegister(&readStringFuncDef, readStringCall);
}
epicsExportRegistrar(iocmd);
