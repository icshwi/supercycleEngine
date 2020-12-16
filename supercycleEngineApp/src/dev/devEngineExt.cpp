/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-15
 */

#include <stdio.h>
#include <string.h>

#include "dlog.hpp"
#include "memreg.hpp"

#include <stringinRecord.h>

#include "devExtension.hpp"
#include "devIO.hpp"

static int sctableSwitch()
{
  if (devio::getScTablePath().compare(SCEMEMREG.CSVHandler.getFilePath()) != 0)
  {
    DLOG(dlog::DEBUG, << " OLD SCEMEMREG.CSVHandler.getFilePath() " << SCEMEMREG.CSVHandler.getFilePath() << " NEW devio::getScTablePath() " << devio::getScTablePath())

    if (SCEMEMREG.CSVHandler.init(devio::getScTablePath()) > 0) return 1;
    // Trigger sctable switch behaviour
    SCEMEMREG.Config.SCESwitchBehaviour(true);
  }
  return 0;
}

static long stringin_init_record(stringinRecord* prec)
{
  if (sctableSwitch() > 0) return 0;
  (void)strcpy(prec->val, devio::getScTable().c_str());
  return 0; /* success */
}

static long stringin_read(stringinRecord* prec)
{
  if (sctableSwitch() > 0) return 0;
  (void)strcpy(prec->val, devio::getScTable().c_str());
  prec->udf = 0;
  return 0; /* success */
}

static DevSupReg devStringinScTable = {
    6,
    NULL,
    NULL,
    (DEVSUPFUN)stringin_init_record,
    NULL,
    (DEVSUPFUN)stringin_read,
    NULL};

#include <epicsExport.h>
extern "C"
{
  epicsExportAddress(dset, devStringinScTable);
  //epicsExportAddress(dset, devStringoutObjProp);
}
