#include <stdlib.h>
#include <dbAccess.h>
#include <devSup.h>
#include <recGbl.h>
#include <alarm.h>
#include <longoutRecord.h>

#include <epicsThread.h>

#include "devext.h"

static long initLongOutDly()
{
    return 0;
}

static long ioLongOutDly(longoutRecord *prec)
{
    epicsThreadSleep(prec->val / 1000000); //[us]
    return 0;
}

//Naming: devXxYyyy

static DevSupReg devLongOutDly = {
    6,
    NULL,
    NULL,
    (DEVSUPFUN)&initLongOutDly,
    NULL,
    (DEVSUPFUN)&ioLongOutDly,
    NULL};

#include <epicsExport.h>
extern "C"
{
    epicsExportAddress(dset, devLongOutDly);
}
