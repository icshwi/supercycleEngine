#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <algorithm> // std::min
#include <stdio.h>
#include <string.h>

//static long initDMux(aSubRecord *pRecord)
//{
//    return 0;
//}

static long ioASubFOut(aSubRecord *prec)
{

    //nea (actual), noa (max)
    memcpy(prec->vala, prec->a, std::min(prec->nea, prec->nova) * sizeof(epicsUInt32));
    memcpy(prec->valb, prec->a, std::min(prec->nea, prec->novb) * sizeof(epicsUInt32));
    memcpy(prec->valc, prec->a, std::min(prec->nea, prec->novc) * sizeof(epicsUInt32));
    memcpy(prec->vald, prec->a, std::min(prec->nea, prec->novd) * sizeof(epicsUInt32));

    prec->neva = std::min(prec->nea, prec->nova);
    prec->nevb = std::min(prec->nea, prec->novb);
    prec->nevc = std::min(prec->nea, prec->novc);
    prec->nevd = std::min(prec->nea, prec->novd);

    return 0;
}

epicsRegisterFunction(ioASubFOut);
