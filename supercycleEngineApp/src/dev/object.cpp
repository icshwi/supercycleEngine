/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#include "object.hpp"
#include "reg.hpp"

namespace SCE
{

static std::string getSwVer()
{
  return SCE_VERSION;
}

static std::string getScTable()
{
  return SCEMEMREG.CSVHandler.getFileName();
}

static std::string getSwBuild()
{
  std::string tmp_ = __DATE__;
  tmp_ += " ";
  tmp_ += __TIME__;
  return tmp_;
}

} // namespace SCE

#define ObjPropRecIn(obj, prop) _ObjPropFunc[#obj][#prop] = obj::get##prop;
namespace dev
{

ObjBase::ObjBase()
{
  ObjPropRecIn(SCE, SwVer);
  ObjPropRecIn(SCE, ScTable);
  ObjPropRecIn(SCE, SwBuild);
}

ObjReg& ObjReg::instance()
{
  static ObjReg instance;
  return instance;
}

} // namespace dev
