/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <string>
#include <map>
#include <functional>

namespace dev
{

  class ObjBase
  {
  public:
    ObjBase();
    void init();

    std::map<std::string, std::map<std::string, std::function<std::string()>>> obj_prop_func;
  };

  class ObjReg : ObjBase
  {
  public:
    ObjReg(){};
    //void add(std::string name, std::function<std::string()> func) { obj_prop_func[name] = func; };
    std::function<std::string()> get(std::string obj, std::string prop) { return obj_prop_func[obj][prop]; };
    static ObjReg &instance();
  };

} // namespace dev

#endif // OBJECT_HPP_
