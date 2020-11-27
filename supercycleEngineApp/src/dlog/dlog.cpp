/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-26
 */

#include "dlog.hpp"
#include <map>

namespace dlog
{
  static std::string func_str_null()
  {
    return "";
  }

  Config::Config()
  {
    this->headers = true;
    this->level = &lv;
    this->tstf = dlog::func_str_null;
  }

  const std::map<dlog::Type, std::string> TypeMap = {
      {DEBUG3, "DEBUG3"},
      {DEBUG2, "DEBUG2"},
      {DEBUG1, "DEBUG1"},
      {DEBUG, "DEBUG"},
      {INFO, "INFO"},
      {WARNING, "WARNING"},
      {ERROR, "ERROR"}};

  Config &Config::instance()
  {
    static Config instance;
    return instance;
  }

  void Config::init(dlog::Type *level_switch, std::function<std::string()> timestamp, bool headers)
  {
    this->level = level_switch;
    this->headers = headers;
    if (timestamp != nullptr)
      this->tstf = timestamp;
    else
      this->tstf = dlog::func_str_null;
  }

  Print::Print(dlog::Type type)
  {
    msglevel = type;
    if (config.headers && (msglevel >= *config.level))
    {
      operator<<(config.tstf() + " " + dlog::TypeMap.at(type) + " ");
    }
  }

  Print::~Print()
  {
    if (opened && (msglevel >= *config.level))
    {
      std::cout << std::endl;
    }
    opened = false;
  }

} // namespace dlog
