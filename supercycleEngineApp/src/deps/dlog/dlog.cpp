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

  const std::map<dlog::LevelTypes, std::string> _LevelTypesMap = {
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

  void Config::init(dlog::LevelTypes *level, std::function<std::string()> timestamp, bool headers)
  {
    _plevel = level;
    _headers = headers;
    _tstf = timestamp != nullptr ? timestamp : dlog::_func_str_dlog;
  }

  Print::Print(dlog::LevelTypes level) : _msglevel(level), _cfg_level(*dlog::Config::instance()._plevel)
  {
    if (_config._headers && (_msglevel >= _cfg_level))
      operator<<(_config._tstf() + " " + dlog::_LevelTypesMap.at(_msglevel) + " ");
  }

  Print::~Print()
  {
    if (_msglevel >= _cfg_level)
      std::cout << std::endl;
  }

} // namespace dlog
