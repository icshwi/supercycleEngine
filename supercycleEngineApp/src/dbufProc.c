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
#include <aaoRecord.h>

#include "test.hpp"

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
static long init_dbuf_aao();
static long init_dbuf_record_aao();
static long write_dbuf_aao();

struct devsup regDevAaoDbuf = {
    5,
    NULL,
    NULL,
    init_dbuf_aao,
    init_dbuf_record_aao,
    write_dbuf_aao};

epicsExportAddress(dset, regDevAaoDbuf);

static long init_dbuf_aao(int after)
{
    print(1, 1111);
}

static long init_dbuf_record_aao(struct aaoRecord *prec)
{
    print(2, 2222);
}

static long write_dbuf_aao(struct aaoRecord *prec)
{
    print(3, 3333);

    return 0;
}
