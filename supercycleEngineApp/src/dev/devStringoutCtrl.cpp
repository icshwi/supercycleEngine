/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "devStringoutCtrl.hpp"
#include "devExtension.hpp"

#include <alarm.h>
#include <dbAccess.h>
#include <devSup.h>
#include <iostream>
#include <recGbl.h>
#include <stdlib.h>

#include <stringoutRecord.h>

namespace devreg
{
std::map<std::string, std::string>& StrOutCtrlMap()
{
  static std::map<std::string, std::string> reg_;
  return reg_;
}
} // namespace devreg

static long initStrOutCtrl(stringoutRecord* prec)
{
  std::string key(prec->name);
  std::string val(prec->val);
  devreg::StrOutCtrlMap()[key] = val;
  return 0;
}

static long ioStrOutCtrl(stringoutRecord* prec)
{
  std::string key(prec->name);
  std::string val(prec->val);
  devreg::StrOutCtrlMap()[key] = val;
  return 0;
}

//Naming: devXxYyyy

static CmnDset devStrOutCtrl = {
    6,
    NULL,
    NULL,
    (DEVSUPFUN)&initStrOutCtrl,
    NULL,
    (DEVSUPFUN)&ioStrOutCtrl,
    NULL};

#include <epicsExport.h>
extern "C"
{
  epicsExportAddress(dset, devStrOutCtrl);
}
