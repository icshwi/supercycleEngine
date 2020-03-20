/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef DEVEXT_H_
#define DEVEXT_H_

#include <devSup.h>

struct DevSupReg
{
    long num; // space for 6 functions
    DEVSUPFUN report;
    DEVSUPFUN init;
    DEVSUPFUN init_record;
    DEVSUPFUN get_ioint_info;
    DEVSUPFUN io;
    DEVSUPFUN special_linconv;
};

struct devPriv
{
    unsigned int seed;
};

#endif // DEVEXT_H_
