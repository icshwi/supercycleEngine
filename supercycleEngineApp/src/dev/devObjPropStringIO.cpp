/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-01
 */

#include <iostream>
#include <vector>

#include <stringinRecord.h>
#include <stringoutRecord.h>

#include "string.h"
#include "devExtension.h"
#include "iobase.hpp"
#include "object.hpp"

struct StrStruc
{
  char m_el[40];
  StrStruc(std::string str)
  {
    strcpy(m_el, str.c_str());
  }
};
static std::vector<StrStruc> l_StrV;

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
  StrStruc str_obj(dev::ObjReg::instance().get(io::db_inp_val(inp_str, "OBJ"), io::db_inp_val(inp_str, "PROP"))());

  l_StrV.push_back(str_obj);
  std::vector<StrStruc>::iterator it = l_StrV.end() - 1;
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
