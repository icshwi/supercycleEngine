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

static long init_dbuf_record_wf(struct waveformRecord *pwave)
{
    print(2, 2222);
}

static long read_dbuf_wf(struct waveformRecord *pwave)
{
    print(3, 3333);
}
