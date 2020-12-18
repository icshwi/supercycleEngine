/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-01
 */

#include <stringinRecord.h>
//#include <stringoutRecord.h>
#include <epicsExport.h>
#include <lsiRecord.h>
#include <waveformRecord.h>

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
static long init_record_StringinObjProp(stringinRecord* prec)
{
  return dev::initRecStrInObjProp<stringinRecord>(prec);
}

static long read_string_StringinObjProp(stringinRecord* prec)
{
  return dev::readRecStrInObjProp<stringinRecord>(prec);
}

//=================================================================================
static long init_record_LsiObjProp(lsiRecord* prec)
{
  prec->len = prec->sizv;
  return dev::initRecStrInObjProp<lsiRecord>(prec);
}

static long read_string_LsiObjProp(lsiRecord* prec)
{
  return dev::readRecStrInObjProp<lsiRecord>(prec);
}

//=================================================================================
long readWaveformStrInObjProp(waveformRecord* prec)
{
  if (dev::recBodyObjProp<waveformRecord>(prec)) return 1;
  dev::StrInFunc* priv = (dev::StrInFunc*)prec->dpvt;

  prec->nelm = priv->_func().size() + 1;
  prec->nord = prec->nelm;
  (void)strncpy((char*)prec->bptr, priv->_func().c_str(), prec->nelm);

  return 0; /* success */
}

static long init_record_WaveformStrInObjProp(waveformRecord* prec)
{
  return dev::initRecStrInObjProp<waveformRecord>(prec);
}

static long read_string_WaveformStrInObjProp(waveformRecord* prec)
{
  return readWaveformStrInObjProp(prec);
}

CMNDSET(WaveformStrInObjProp)
CMNDSET(LsiObjProp)
CMNDSET(StringinObjProp)
