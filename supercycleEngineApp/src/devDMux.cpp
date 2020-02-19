#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <algorithm> // std::min

static void copyArrs(epicsUInt32 *inarr, epicsUInt32 *outarr, epicsUInt32 n)
{
    int i = 0;
    for (i = 0; i < n; ++i)
        outarr[i] = inarr[i];
}

//static long initDMux(aSubRecord *pRecord)
//{
//    return 0;
//}

// 1 to 4 DMUX
static long ioDMux(aSubRecord *prec)
{
    epicsUInt32 *a = (epicsUInt32 *)prec->a;
    //epicsUInt32 len = prec->noa;
    epicsUInt32 *b = (epicsUInt32 *)prec->b;

    epicsUInt32 *vala = (epicsUInt32 *)prec->vala;
    epicsUInt32 *valb = (epicsUInt32 *)prec->valb;
    epicsUInt32 *valc = (epicsUInt32 *)prec->valc;
    epicsUInt32 *vald = (epicsUInt32 *)prec->vald;

    switch (*b)
    {
    case 0:
        copyArrs(a, vala, std::min(prec->noa, prec->nova));
        break;
    case 1:
        copyArrs(a, valb, std::min(prec->noa, prec->novb));
        break;
    case 2:
        copyArrs(a, valc, std::min(prec->noa, prec->novc));
        break;
    case 3:
        copyArrs(a, vald, std::min(prec->noa, prec->novd));
        break;
    default:
        break;
    }

    return 0;
}

// Register the function

//epicsRegisterFunction(initDMux);
epicsRegisterFunction(ioDMux);
