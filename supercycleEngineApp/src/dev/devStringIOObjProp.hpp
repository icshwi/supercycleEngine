/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-17
 */

#pragma once

#include <alarm.h>
#include <dbAccess.h>
#include <lsiRecord.h>
#include <recGbl.h>

#include <string.h>
#include <string>

#include "devExtension.hpp"
#include "dlog.hpp"
#include "object.hpp"

namespace dev
{
struct StrInFunc
{
  std::function<std::string()> _func;
  StrInFunc(std::function<std::string()> func) : _func(func){};
};

template <typename T>
long initRecStrInObjProp(T* prec)
{
  char* parm = prec->inp.value.instio.string;
  std::string inp_str(parm);
  StrInFunc* priv = new StrInFunc(dev::ObjReg::instance().get(dev::db_inp_val(inp_str, "OBJ"), dev::db_inp_val(inp_str, "PROP")));
  if (!priv)
  {
    recGblRecordError(S_db_noMemory, (void*)priv, "failed to allocate private struct");
    return S_db_noMemory;
  }

  prec->dpvt = (void*)priv;
  return 0; /* success */
}

template <typename T>
long recBodyObjProp(T* prec)
{
  StrInFunc* priv = (StrInFunc*)prec->dpvt;
  if (!priv)
  {
    (void)recGblSetSevr(prec, COMM_ALARM, INVALID_ALARM);
    return 1;
  }
  //if (std::is_same<T, lsiRecord>::value)
  //  prec->len = priv->_func().size();
  //(void)strncpy((char*)prec->val, priv->_func().c_str(), priv->_func().size());
  prec->udf = 0;
  return 0; /* success */
}

template <typename T>
long readRecStrInObjProp(T* prec)
{
  if (recBodyObjProp<T>(prec)) return 1;
  StrInFunc* priv = (StrInFunc*)prec->dpvt;

  (void)strncpy((char*)prec->val, priv->_func().c_str(), priv->_func().size());
  return 0; /* success */
}

} // namespace dev
