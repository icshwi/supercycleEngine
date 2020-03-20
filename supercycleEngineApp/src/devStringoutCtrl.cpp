/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "devStringoutCtrl.hpp"

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

std::map<std::string, std::string> RegisteredStrOutMap;

static long initStrOutCtrl(stringoutRecord *prec)
{
    std::string key(prec->name);
    std::string val(prec->val);
    RegisteredStrOutMap[key] = val;
    return 0;
}

static long ioStrOutCtrl(stringoutRecord *prec)
{
    std::string key(prec->name);
    std::string val(prec->val);
    RegisteredStrOutMap[key] = val;
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
