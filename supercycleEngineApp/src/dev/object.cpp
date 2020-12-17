/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#include <dirent.h>
#include <sys/types.h>

#include "devIO.hpp"
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

namespace SYS
{

static std::string getScTables()
{
  std::string tmp_ = {};

  DIR* dirp = opendir(devio::getScTableDir().c_str());
  struct dirent* dp;
  while ((dp = readdir(dirp)) != NULL)
  {
    tmp_.append(dp->d_name);
    tmp_.push_back(' ');
  }
  closedir(dirp);
  tmp_.push_back('\0');

  return tmp_;
}

} // namespace SYS

#define ObjPropRecIn(obj, prop) _ObjPropFunc[#obj][#prop] = obj::get##prop;
namespace dev
{

ObjBase::ObjBase()
{
  ObjPropRecIn(SCE, SwVer);
  ObjPropRecIn(SCE, ScTable);
  ObjPropRecIn(SCE, SwBuild);
  ObjPropRecIn(SYS, ScTables);
}

ObjReg& ObjReg::instance()
{
  static ObjReg instance;
  return instance;
}

} // namespace dev
