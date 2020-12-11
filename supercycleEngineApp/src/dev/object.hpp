/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#pragma once

#include <functional>
#include <map>
#include <string>

namespace dev
{

class ObjBase
{
private:
  friend class ObjReg;
  ObjBase();
  std::map<std::string, std::map<std::string, std::function<std::string()>>> _ObjPropFunc;
};

class ObjReg
{
public:
  ObjReg(){};
  std::function<std::string()> get(std::string obj, std::string prop) { return _ObjBase._ObjPropFunc[obj][prop]; };
  static ObjReg& instance();

private:
  ObjBase _ObjBase;
};

} // namespace dev
