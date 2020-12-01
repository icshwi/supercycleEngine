/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-26
 */

#include "dlog.hpp"
#include <map>

namespace dlog
{
  static std::string func_str_dlog()
  {
    return "DLOG";
  }

  Config::Config() : m_tstf(dlog::func_str_dlog)
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
    m_level = level;
    m_headers = headers;
    m_tstf = timestamp != nullptr ? timestamp : dlog::func_str_dlog;
  }

  Print::Print(dlog::Type level)
  {
    m_msglevel = level;
    if (m_config.m_headers && (m_msglevel >= *m_config.m_level))
      operator<<(m_config.m_tstf() + " " + dlog::TypeMap.at(m_msglevel) + " ");
  }

  Print::~Print()
  {
    if (m_msglevel >= *m_config.m_level)
      std::cout << std::endl;
  }

} // namespace dlog
