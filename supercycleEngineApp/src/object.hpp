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

  class ObjProbBase
  {
  public:
    ObjProbBase() { init(); };
    void init();

  protected:
    std::map<std::string, std::function<std::string()>> prop_func;
  };

  class ObjPropRegistry : ObjProbBase
  {
  public:
    ObjPropRegistry(){};
    void add(std::string name, std::function<std::string()> func) { prop_func[name] = func; };
    std::function<std::string()> get(std::string name) { return prop_func[name]; };
    static ObjPropRegistry &instance();
  };

} // namespace dev

#endif // OBJECT_HPP_

//#define OBJECT_BEGIN(klass) OBJECT_BEGIN1(klass)

// #define OBJECT1_BEGIN(klass)                   \
//   typedef std::string (klass::*Object1)(void); \
//   static ObjPropClass<Object1> ObjProp;        \
//   void OBJECT1Func()

// #define OBJECT1_PROP_ADD(NAME, ADD) ObjProp.add(NAME, ADD);
// #define OBJECT1_PROP_GET(NAME) ObjProp.get(NAME);

// OBJECT1_BEGIN(SCE)
// {
//   OBJECT1_PROP_ADD("Sw Version", &SCE::getSwVersion);
// }
// OBJECT1_PROP_GET("Sw Version");

// OBJECT1_BEGIN(SCE)
// {
//   OBJECT1_PROP("Sw Version", &SCE::getSwVersion);
// }

//typedef std::string (SCE::*OBJECT)();
//std::map<std::string, OBJECT> ObjPropMap;

//void ObjProp()
//{
//  ObjPropMap["Sw Version"] = &SCE::getSwVersion;
//}

// template <class OBJ>
// void ObjProp<OBJ>::add(std::string name, OBJ func)
// {
//   ObjPropMap[name] = func;
// }

// typedef std::string (SCE::*OBJECT1)();
// ObjProp<OBJECT1> ObjSce;
//void test()
//{
//  ObjSce.add("test", &SCE::getSwVersion);
//}

//ObjSce.add("Sw Version", &SCE::getSwVersion);
