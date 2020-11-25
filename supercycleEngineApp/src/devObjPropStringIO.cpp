#include <stringoutRecord.h>
#include <stringinRecord.h>

//#include "devObj.h"

#include "devext.h"
#include "iobase.hpp"

#include <iostream>
#include <dbAccessDefs.h>

#include <string.h>
#include <stdlib.h>

#include <epicsStdio.h>
#include <epicsVersion.h>
#include <epicsTime.h>
#include <epicsFindSymbol.h>

#include <dbAccess.h>
#include <devSup.h>
#include <stringinRecord.h>
#include <recGbl.h>
#include <envDefs.h>

static long stringin_init(int pass)
{
  if (pass)
    return 0;

  return 0;
}

static long stringin_init_record(stringinRecord *pr)
{
  char *parm = pr->inp.value.instio.string;

  std::string tmp_str(parm);

  std::cout << " xxxxxxxxxxxxxxxxxxxxxxxxx " << tmp_str << std::endl;

  std::cout << io::db_inp_val(tmp_str, "OBJ") << std::endl;
  std::cout << io::db_inp_val(tmp_str, "PROP") << std::endl;
  //std::cout << io::db_inp_val(tmp_str, "PROP") << std::endl;

  return 0; /* success */
}

static long stringin_read(stringinRecord *pr)
{

  return (0); /* success */
}

static DevSupReg devStrInFromStr = {
    6,
    NULL,
    (DEVSUPFUN)&stringin_init,
    (DEVSUPFUN)&stringin_init_record,
    NULL,
    (DEVSUPFUN)&stringin_read,
    NULL};

#include <epicsExport.h>
extern "C"
{
  //epicsExportAddress(dset, devSOFromString);
  epicsExportAddress(dset, devStrInFromStr);
}
