/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#include "object.hpp"
#include "sce.hpp"

OBJECT1_BEGIN(SCE)
{
  OBJECT1_PROP("Sw Version", &SCE::getSwVersion);
}

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
