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

static long init_dbuf_aao(aaoRecord *prec)
{
    /* OUT must be a CONSTANT or a PV_LINK or a DB_LINK or a CA_LINK*/

    /*    switch (prec->out.type)
    {
    case CONSTANT:
        prec->nord = 0;
        break;
    case PV_LINK:
    case DB_LINK:
    case CA_LINK:
        break;
    default:
        recGblRecordError(S_db_badField, prec,
                          "devAaoSoft (init_record) Illegal OUT field");
        return (S_db_badField);
    }
*/
    return 0;
}

static int sizeofTypes[] = {MAX_STRING_SIZE, 1, 1, 2, 2, 4, 4, 4, 8, 2};

static long init_dbuf_record_aao(struct aaoRecord *paao)
{
    /* aao record does not allocate bptr. Why not? */
    if (!paao->bptr)
    {
        if (paao->ftvl > DBF_ENUM)
            paao->ftvl = 2;
        paao->bptr = (char *)calloc(paao->nelm, sizeofTypes[paao->ftvl]);
    }

    /* aao.out must be a CONSTANT or a PV_LINK or a DB_LINK or a CA_LINK*/
    switch (paao->out.type)
    {
    case (CONSTANT):
        paao->nord = 0;
        break;
    case (PV_LINK):
    case (DB_LINK):
    case (CA_LINK):
        break;
    default:
        recGblRecordError(S_db_badField, (void *)paao,
                          "devAaoSoft (init_record) Illegal INP field");
        return (S_db_badField);
    }
    return (0);
}

static long write_dbuf_aao(struct aaoRecord *paao)
{
    long status, nRequest;

    nRequest = paao->nelm;

    int intaa[] = {1, 2, 3, 4};

    status = dbPutLink(&paao->out, paao->ftvl, intaa, 4);
    /*If dbGetLink got no values leave things as they were*/
    if (nRequest > 0)
        paao->nord = nRequest;

    return (0);
}
