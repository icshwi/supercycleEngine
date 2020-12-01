/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-01
 */

#include <iostream>
#include <vector>

#include <stringinRecord.h>
//#include <stringoutRecord.h>
#include <epicsExport.h>

#include "iobase.hpp"
#include "object.hpp"
#include "string.h"
#include "devExtension.h"

#define STRIN_MAX_LEN 40
struct StrInStruc
{
  char m_el[STRIN_MAX_LEN];
  StrInStruc(std::string str)
  {
    strncpy(m_el, str.c_str(), STRIN_MAX_LEN - 1);
    m_el[STRIN_MAX_LEN - 1] = '\0';
  }
};
static std::vector<StrInStruc> s_StrInV;

static long stringin_init(int pass)
{
  //dlog::Print(dlog::INFO) << "--------------- stringin_init ---------------";
  if (pass)
    return 0;

  return 0;
}

static long stringin_init_record(stringinRecord *pr)
{
  char *parm = pr->inp.value.instio.string;

  std::string inp_str(parm);
  std::string name_str(pr->name);
  StrInStruc str_obj(dev::ObjReg::instance().get(io::db_inp_val(inp_str, "OBJ"), io::db_inp_val(inp_str, "PROP"))());

  s_StrInV.push_back(str_obj);
  std::vector<StrInStruc>::iterator it = s_StrInV.end() - 1;
  pr->dpvt = (void *)&(*it);
  //std::cout << "----------------= " << (char *)pr->dpvt << std::endl;
  return 0; /* success */
}

static long stringin_read(stringinRecord *pr)
{
  (void)strcpy(pr->val, (char *)pr->dpvt);
  pr->udf = 0;
  return 0; /* success */
}

static DevSupReg devObjPropStringIn = {
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
  epicsExportAddress(dset, devObjPropStringIn);
}
