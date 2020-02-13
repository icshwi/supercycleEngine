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

/* Create the dset for devAiSecond */
static long init_record();
static long init_ai();
static long read_ai();
struct
{
    long number;
    DEVSUPFUN report;
    DEVSUPFUN init;
    DEVSUPFUN init_record;
    DEVSUPFUN get_ioint_info;
    DEVSUPFUN read_ai;
    DEVSUPFUN special_linconv;
} devAiSecond = {
    6,
    NULL,
    init_ai,
    init_record,
    NULL,
    read_ai,
    NULL};
epicsExportAddress(dset, devAiSecond);

/************************************************************************/
/* Ai Record								*/
/*  INP = "hostname-or-ipaddress:data-number"				*/
/************************************************************************/

/* init_ai for debug */
static long init_ai(int after)
{
}

static long init_record(struct aiRecord *pai)
{
}

static long read_ai(struct aiRecord *pai)
{
}