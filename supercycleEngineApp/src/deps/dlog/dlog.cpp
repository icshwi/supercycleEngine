/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-26
 */

#include "dlog.hpp"
#include <map>

namespace dlog
{
  static std::string _func_str_dlog()
  {
    return "DLOG";
  }

  Config::Config() : _tstf(dlog::_func_str_dlog)
  {
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

  void Config::init(dlog::Type *level, std::function<std::string()> timestamp, bool headers)
  {
    _level = level;
    _headers = headers;
    _tstf = timestamp != nullptr ? timestamp : dlog::_func_str_dlog;
  }

  Print::Print(dlog::Type level)
  {
    _msglevel = level;
    if (_config._headers && (_msglevel >= *_config._level))
      operator<<(_config._tstf() + " " + dlog::TypeMap.at(_msglevel) + " ");
  }

  Print::~Print()
  {
    if (_msglevel >= *_config._level)
      std::cout << std::endl;
  }

} // namespace dlog
