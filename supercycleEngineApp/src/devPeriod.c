#include <stdlib.h>
#include <dbAccess.h>
#include <devSup.h>
#include <recGbl.h>
#include <alarm.h>
#include <aiRecord.h>
#include <epicsExport.h>

#include "devext.h"
#include "cpp2cApi.hpp"

/* Create the dset */
static long initPeriod();
static long ioPeriod();

//Naming: devXxYyyy

struct DevSupReg devAiPeriod = {
    6,
    NULL,
    NULL,
    initPeriod,
    NULL,
    ioPeriod,
    NULL};

epicsExportAddress(dset, devAiPeriod);

extern int sc_prd_us;

static long initPeriod(int test)
{
    return 0;
}

static long ioPeriod(struct aiRecord *prec)
{
    //struct devPriv *priv = prec->dpvt;
    prec->rval = sc_prd_us;
    return 0;
}
