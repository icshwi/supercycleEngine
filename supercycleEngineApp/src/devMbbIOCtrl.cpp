/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-10-28
 */

#include "devext.h"

#include "devMbbIOCtrl.hpp"

#include <stdlib.h>
#include <iostream>

#include <dbAccess.h>
#include <devSup.h>
#include <recGbl.h>
#include <alarm.h>
#include <mbboRecord.h>

std::map<std::string, epicsUInt32> RegisteredMbboMap;

static long initMbboCtrl(mbboRecord *prec)
{
  std::string key(prec->name);
  epicsUInt32 rval = prec->rval;
  RegisteredMbboMap[key] = rval;
  return 0;
}

static long ioMbboCtrl(mbboRecord *prec)
{
  std::string key(prec->name);
  epicsUInt32 rval = prec->rval;
  RegisteredMbboMap[key] = rval;
  return 0;
}

//Naming: devXxYyyy

static DevSupReg devMbboCtrl = {
    6,
    NULL,
    NULL,
    (DEVSUPFUN)&initMbboCtrl,
    NULL,
    (DEVSUPFUN)&ioMbboCtrl,
    NULL};

#include <epicsExport.h>
extern "C"
{
  epicsExportAddress(dset, devMbboCtrl);
}
