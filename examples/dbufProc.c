#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alarm.h"
#include "cvtTable.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include "recGbl.h"
#include "recSup.h"
#include "devSup.h"
#include "aiRecord.h"
#include "link.h"
#include "epicsExport.h"
//#include "devAiSecond.h"
#include "waveformRecord.h"

#include "test.hpp"

/* Create the dset */
static long init_dbuf_wf();
static long init_dbuf_record_wf();
static long read_dbuf_wf();

struct
{
    long number;
    DEVSUPFUN report;
    DEVSUPFUN init_wave;
    DEVSUPFUN init_record_wave;
    DEVSUPFUN get_ioint_info;
    DEVSUPFUN read_wave;
    DEVSUPFUN special_linconv;
} devWaveDbuf = {
    6,
    NULL,
    init_dbuf_wf,
    init_dbuf_record_wf,
    NULL,
    read_dbuf_wf,
    NULL};
epicsExportAddress(dset, devWaveDbuf);

static long init_dbuf_wf(int after)
{
    print(1, 1111);
}

static long init_dbuf_record_wf(struct waveformRecord *prec)
{
    print(2, 2222);
}

static long read_dbuf_wf(struct waveformRecord *prec)
{
    print(3, 3333);
    long nRequest = prec->nelm;

    int inta[10] = {5, 6, 7, 8};
    prec->val = inta;
    prec->bptr = inta;

    dbPutLink(&prec->inp, DBR_ULONG, &inta, 1);
    //dbPutLink(&prec->inp, prec->ftvl, inta, 4);

    /*
    if (!prec->rarm)
    {
        // If not "armed" then put
        prec->rarm = 0;
        db_post_events(prec, &prec->rarm, DBE_VALUE | DBE_ARCHIVE);
        dbPutLink(&prec->inp, prec->ftvl, prec->bptr, prec->nord);
    }
    else
    {
        // If "armed" then get
        if (prec->inp.type != CONSTANT)
            (void)dbGetLink(&prec->inp, prec->ftvl, prec->bptr, 0, &nRequest);
        if (nRequest > 0)
        {
            prec->nord = nRequest;
            if (prec->tsel.type == CONSTANT &&
                prec->tse == epicsTimeEventDeviceTime)
                dbGetTimeStamp(&prec->inp, &prec->time);
        }
    }

    int *tmp = (int *)prec->bptr;

    print(tmp[0], 10);
    */

    return 0;
}
