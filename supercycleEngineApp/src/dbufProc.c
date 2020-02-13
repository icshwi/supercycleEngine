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

/* Create the dset */
static long init_dbuf_wave();
static long init_dbuf_record_wave();
static long read_dbuf_wave();

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
    init_dbuf_wave,
    init_dbuf_record_wave,
    NULL,
    read_dbuf_wave,
    NULL};
epicsExportAddress(dset, devWaveDbuf);

static long init_dbuf_wave(int after)
{
}

static long init_dbuf_record_wave(struct waveformRecord *pwave)
{
}

static long read_dbuf_wave(struct waveformRecord *pwave)
{
}
