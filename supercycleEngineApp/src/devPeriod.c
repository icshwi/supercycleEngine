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
static long init_Period();
static long read_Period();

//Naming: devXxYyyy

struct DevSupReg devAiPeriod = {
    6,
    NULL,
    NULL,
    init_Period,
    NULL,
    read_Period,
    NULL};

epicsExportAddress(dset, devAiPeriod);

extern int sc_prd_us;

static long init_Period(int test)
{
    return 0;
}

static long read_Period(struct aiRecord *prec)
{
    //struct devPriv *priv = prec->dpvt;
    prec->rval = sc_prd_us;
    return 0;
}
