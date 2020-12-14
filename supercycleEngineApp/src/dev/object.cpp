/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#include "object.hpp"
#include "ioblock.hpp"

namespace SCE
{

static std::string getSwVersion()
{
  return SCE_VERSION;
}

static std::string getScTable()
{
  return io::RegisteredIOBlock().CSVTab.getFileName();
}

} // namespace SCE
namespace dev
{

ObjBase::ObjBase()
{
  _ObjPropFunc["SCE"]["SwVer"] = SCE::getSwVersion;
  _ObjPropFunc["SCE"]["ScTable"] = SCE::getScTable;
}

ObjReg& ObjReg::instance()
{
  static ObjReg instance;
  return instance;
}

} // namespace dev
