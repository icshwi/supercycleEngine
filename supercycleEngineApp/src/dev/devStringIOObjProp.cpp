/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-01
 */

#include <string>
#include <functional>

#include <stringinRecord.h>
//#include <stringoutRecord.h>
#include <epicsExport.h>
#include <recGbl.h>
#include <dbAccess.h>
#include <alarm.h>

#include "iobase.hpp"
#include "object.hpp"
#include "string.h"
#include "devExtension.h"

struct StrInFunc
{
  std::function<std::string()> m_func;
  StrInFunc(std::function<std::string()> func) : m_func(func){};
};

static long stringin_init(int pass)
{
  //dlog::Print(dlog::INFO) << "--------------- stringin_init ---------------";
  if (pass)
    return 0;

  return 0;
}

static long stringin_init_record(stringinRecord *prec)
{
  char *parm = prec->inp.value.instio.string;
  std::string inp_str(parm);
  StrInFunc *priv = new StrInFunc(dev::ObjReg::instance().get(io::db_inp_val(inp_str, "OBJ"), io::db_inp_val(inp_str, "PROP")));
  if (!priv)
  {
    recGblRecordError(S_db_noMemory, (void *)priv, "failed to allocate private struct");
    return S_db_noMemory;
  }

  prec->dpvt = (void *)priv;
  //std::cout << "----------------= " << priv->m_func() << std::endl;
  return 0; /* success */
}

static long stringin_read(stringinRecord *prec)
{
  StrInFunc *priv = (StrInFunc *)prec->dpvt;
  if (!priv)
  {
    (void)recGblSetSevr(prec, COMM_ALARM, INVALID_ALARM);
    return 0;
  }

  (void)strcpy(prec->val, priv->m_func().c_str());

  prec->udf = 0;
  return 0; /* success */
}

static DevSupReg devStringinObjProp = {
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
  epicsExportAddress(dset, devStringinObjProp);
}
