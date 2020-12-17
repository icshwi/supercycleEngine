/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-01
 */

#include <stringinRecord.h>
//#include <stringoutRecord.h>
#include <epicsExport.h>
#include <lsiRecord.h>

#include "devStringIOObjProp.hpp"
#include "dlog.hpp"

// static long init_stringin(int pass)
// {
//   if (pass)
//     return 0;

//   return 0;
// }

//stringinObjProp
//===============
static long init_record_stringinObjProp(stringinRecord* prec)
{
  return dev::initRecStrInObjProp<stringinRecord>(prec);
}

static long read_string_stringinObjProp(stringinRecord* prec)
{
  return dev::readRecStrInObjProp<stringinRecord>(prec);
}

static DevSupReg devStringinObjProp = {
    6,
    NULL,
    NULL,
    (DEVSUPFUN)init_record_stringinObjProp,
    NULL,
    (DEVSUPFUN)read_string_stringinObjProp,
    NULL};

//=================================================================================
static long init_record_lsiObjProp(lsiRecord* prec)
{
  prec->len = prec->sizv;
  return dev::initRecStrInObjProp<lsiRecord>(prec);
}

static long read_string_lsiObjProp(lsiRecord* prec)
{
  return dev::readRecStrInObjProp<lsiRecord>(prec);
}

static lsidset devLsiObjProp = {
    5,
    NULL,
    NULL,
    (DEVSUPFUN)init_record_lsiObjProp,
    NULL,
    (DEVSUPFUN)read_string_lsiObjProp};

#include <epicsExport.h>
extern "C"
{
  epicsExportAddress(dset, devStringinObjProp);
  //epicsExportAddress(dset, devStringoutObjProp);
  epicsExportAddress(dset, devLsiObjProp);
}
