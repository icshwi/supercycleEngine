#include <stdlib.h>
#include <dbAccess.h>
#include <devSup.h>
#include <recGbl.h>
#include <alarm.h>

//#include <aiRecord.h>
#include <longinRecord.h>

#include "devext.h"
//#include "cpp2cApi.hpp"
#include <iostream>

extern int sc_prd_us;

static long initPeriod(int test)
{
    return 0;
}

static long ioPeriod(longinRecord *prec)
{
    //struct devPriv *priv = prec->dpvt;
    //prec->val = (epicsInt32)sc_prd_us;
    prec->val = sc_prd_us;
    prec->udf = 0;
    std::cout << "AAAAAAAAAAAAAAAA" << std::endl;
    return 0;
}

//Naming: devXxYyyy

static DevSupReg devLonginPeriod = {
    6,
    NULL,
    NULL,
    (DEVSUPFUN)&initPeriod,
    NULL,
    (DEVSUPFUN)&ioPeriod,
    NULL};

#include <epicsExport.h>
extern "C"
{
    epicsExportAddress(dset, devLonginPeriod);
}
