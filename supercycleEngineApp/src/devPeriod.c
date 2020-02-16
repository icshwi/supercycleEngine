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

struct DevSupReg regDevPeriod = {
    6,
    NULL,
    NULL,
    init_Period,
    NULL,
    read_Period,
    NULL};

epicsExportAddress(dset, regDevPeriod);

static long init_Period(int test)
{
    return 0;
}

static long read_Period(struct aiRecord *prec)
{
    struct devState *priv = prec->dpvt;

    prec->rval++;

    return 0;
}
