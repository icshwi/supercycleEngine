/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#include "object.hpp"
#include "sce.hpp"

namespace dev
{

  ObjBase::ObjBase()
  {
    m_ObjPropFunc["SCE"]["SwVer"] = SCE::getSwVersion;
  }

  ObjReg &ObjReg::instance()
  {
    static ObjReg instance;
    return instance;
  }

} // namespace dev
