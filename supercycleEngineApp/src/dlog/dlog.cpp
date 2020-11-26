/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-26
 */

#include "dlog.hpp"
#include <map>

namespace dlog
{

  const std::map<dlog::Type, std::string> TypeMap = {
      {DEBUG3, "DEBUG3"},
      {DEBUG2, "DEBUG2"},
      {DEBUG1, "DEBUG1"},
      {DEBUG, "DEBUG"},
      {INFO, "INFO"},
      {WARNING, "WARNING"},
      {ERROR, "ERROR"}};

  Config::Config(bool hdr, dlog::Type *lvl)
  {
    init(hdr, lvl);
  }

  Config &Config::instance()
  {
    static Config instance;
    return instance;
  }

  void Config::init(bool hdr, dlog::Type *lvl)
  {
    headers = hdr;
    level = lvl;
  }

  Print::Print(dlog::Type type)
  {
    msglevel = type;
    if (config.headers && (msglevel >= *config.level))
    {
      operator<<(DLOG_TST_NOW + " " + dlog::TypeMap.at(type) + " ");
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
