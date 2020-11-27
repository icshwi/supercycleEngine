/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#include "object.hpp"

namespace dev
{

  std::string SoftwareVersion_test()
  {
    return "SoftwareVersion 9999999";
  }

  ObjBase::ObjBase()
  {
    init();
  }

  void ObjBase::init()
  {
    obj_prop_func["SCE"]["SoftwareVersion"] = dev::SoftwareVersion_test;
  }

  ObjReg &ObjReg::instance()
  {
    static ObjReg instance;
    return instance;
  }

} // namespace dev
