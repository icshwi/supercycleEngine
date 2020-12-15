/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-15
 */

#include <stdio.h>
#include <string.h>

#include "dlog.hpp"
#include "ioblock.hpp"

#include <stringinRecord.h>

#include "devExtension.hpp"

static int sctableSwitch()
{
  if (REGIO.getScTablePath().compare(REGIO.CSVTab.getFilePath()) != 0)
  {
    DLOG(dlog::DEBUG, << " OLD REGIO.CSVTab.getFilePath() " << REGIO.CSVTab.getFilePath() << " NEW REGIO.getScTablePath() " << REGIO.getScTablePath())

    if (REGIO.CSVTab.init(REGIO.getScTablePath()) > 0) return 1;
    // Trigger sctable switch behaviour
    REGIO.SCEConfig_yml.SCESwitchBehaviour(true);
  }
  return 0;
}

static long stringin_init_record(stringinRecord* prec)
{
  if (sctableSwitch() > 0) return 0;
  (void)strcpy(prec->val, REGIO.getScTable().c_str());
  return 0; /* success */
}

static long stringin_read(stringinRecord* prec)
{
  if (sctableSwitch() > 0) return 0;
  (void)strcpy(prec->val, REGIO.getScTable().c_str());
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
