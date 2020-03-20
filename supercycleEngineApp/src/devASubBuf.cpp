/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

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

extern "C"
{
    epicsRegisterFunction(ioASubBuf);
}
