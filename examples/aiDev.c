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
//#include "waveformRecord.h"
#include <aiRecord.h>
#include <dbCommon.h>

#include "cpp2cApi.hpp"

struct devsup
{
    long number;
    DEVSUPFUN report;
    DEVSUPFUN init;
    DEVSUPFUN init_record;
    DEVSUPFUN get_ioint_info;
    DEVSUPFUN io;
};

/* Create the dset */
static long init_dbuf_ai();
static long init_dbuf_record_ai();
static long read_dbuf_ai();

struct devsup regDevAiDbuf = {
    5,
    NULL,
    NULL,
    init_dbuf_ai,
    init_dbuf_record_ai,
    read_dbuf_ai};

epicsExportAddress(dset, regDevAiDbuf);

static long init_dbuf_ai(int test)
{
    return 0;
}

static long init_dbuf_record_ai(struct aiRecord *precord)
{

    return 0;
}

static long read_dbuf_ai(struct aiRecord *precord)
{
    read_ai(precord);
    //regDevReadArray((dbCommon *)prec, prec->nelm);
    //static long aa[] = {5, 6, 7, 8};
    //dbGetLink(&prec->inp, prec->ftvl, aa, 0, 4);
    //dbPutLink(&prec->inp, DBR_ULONG, aa, 4);
    //dbGetLink(&prec->inp, DBR_ULONG, );
    return 0;
}
