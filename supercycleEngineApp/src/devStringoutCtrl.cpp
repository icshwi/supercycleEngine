#include <stdlib.h>
#include <dbAccess.h>
#include <devSup.h>
#include <recGbl.h>
#include <alarm.h>

//#include <aiRecord.h>
//#include <longinRecord.h>
#include <stringoutRecord.h>

#include "devext.h"
#include <iostream>
#include "ioblock.hpp"

#include "engineInit.hpp"

static long initStrOutCtrl(stringoutRecord *prec)
{
    std::string key(prec->name);
    std::string val(prec->val);
    io_block.dbCtrlArgs[key] = val;
    return 0;
}

static long ioStrOutCtrl(stringoutRecord *prec)
{
    std::string key(prec->name);
    std::string val(prec->val);
    io_block.dbCtrlArgs[key] = val;
    return 0;
}

//Naming: devXxYyyy

static DevSupReg devStrOutCtrl = {
    6,
    NULL,
    NULL,
    (DEVSUPFUN)&initStrOutCtrl,
    NULL,
    (DEVSUPFUN)&ioStrOutCtrl,
    NULL};

#include <epicsExport.h>
extern "C"
{
    epicsExportAddress(dset, devStrOutCtrl);
}
