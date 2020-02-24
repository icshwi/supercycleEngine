#include <stdio.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <algorithm> // std::min
//#include <stdio.h>
#include <string.h>

static long ioASubBuf(aSubRecord *prec)
{
    memcpy(prec->vala, prec->a, std::min(prec->nea, prec->nova) * sizeof(epicsUInt32));
    prec->neva = std::min(prec->nea, prec->nova);
    return 0;
}

epicsRegisterFunction(ioASubBuf);
