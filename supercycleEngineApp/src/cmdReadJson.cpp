#include "cmdReadJson.hpp"

#include <iocsh.h>
#include <epicsExport.h>

#include <iostream>
#include <fstream>

JsonRootV &RegisteredJsonRoot()
{
    static JsonRootV jr;
    return jr;
}

void JsonRootV::init(std::string fname)
{
    JsonRootV &jr = RegisteredJsonRoot();
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
static const iocshFuncDef printFuncDef = {"readJson", 1, jsonArgs};

static void readJson(const iocshArgBuf *arg)
{
    JsonRootV &jr = RegisteredJsonRoot();

    jr.init(arg->sval);
}

static void jsoncmd(void)
{
    iocshRegister(&printFuncDef, readJson);
}
epicsExportRegistrar(jsoncmd);
