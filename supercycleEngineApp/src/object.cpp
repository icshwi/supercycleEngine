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

  //ObjPropRegistry::instance().add("SoftwareVersion", test1);

  ObjPropRegistry &ObjPropRegistry::instance()
  {
    static ObjPropRegistry instance;
    return instance;
  }

  void ObjProbBase::init()
  {
    prop_func["SoftwareVersion"] = dev::SoftwareVersion_test;
  }

} // namespace dev
