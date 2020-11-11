/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <iostream>
#include <map>

template <class OBJ>
class ObjPropClass
{
public:
  ObjPropClass(){};
  void add(std::string name, OBJ func) { ObjPropMap[name] = func; };

  std::map<std::string, OBJ> ObjPropMap;
};

//#define OBJECT_BEGIN(klass) OBJECT_BEGIN1(klass)

#define OBJECT1_BEGIN(klass)                   \
  typedef std::string (klass::*Object1)(void); \
  ObjPropClass<Object1> ObjProp;               \
  void OBJECT1Func()

#define OBJECT1_PROP(NAME, ADD) ObjProp.add(NAME, ADD);

#endif // OBJECT_HPP_
