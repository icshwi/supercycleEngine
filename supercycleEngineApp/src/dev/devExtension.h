/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef DEVEXTENSION_H_
#define DEVEXTENSION_H_

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
typedef struct DevSupReg DevSupReg;

// struct DevPriv
// {
//   unsigned int seed;
// };

#endif // DEVEXTENSION_H_
