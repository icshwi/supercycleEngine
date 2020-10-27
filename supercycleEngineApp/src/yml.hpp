/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-10-12
 */

#ifndef YML_HPP_
#define YML_HPP_

#include "scenv.hpp"

#include <epicsTypes.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <map>

//https://github.com/jbeder/yaml-cpp/wiki/Tutorial

namespace io
{

  class YmlNode
  {
  protected:
    std::string filename;
    YAML::Node node;
    //std::vector<std::string> keys;

  public:
    //YmlNode(std::string fname);
    YmlNode(){};
    virtual int init(std::string fname);
  };

  class YmlInhibitEvt : public YmlNode
  {
  public:
    YmlInhibitEvt(std::string fname);
    YmlInhibitEvt(){};
    int init(std::string fname);
    std::vector<std::string> getInhEvt();
    //uint getEvtCode(std::string key) { return evtm[key]; };
    //std::map<std::string, uint> getEvtMap() { return evtm; };

  private:
    std::vector<std::string> inhevtv;
  };

  // class YmlMEvt : public YmlNode
  // {
  // public:
  //   //JsonEVT(std::string fname);
  //   YmlMEvt(){};
  //   int init(std::string fname);
  //   uint getEvtCode(std::string key) { return evtm[key]; };
  //   std::map<std::string, uint> getEvtMap() { return evtm; };

  // private:
  //   std::map<std::string, uint> evtm;
  // };

} // namespace io

#endif // YML_HPP_
