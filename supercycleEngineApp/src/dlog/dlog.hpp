/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef DLOG_HPP_
#define DLOG_HPP_

/**
 * Debug Log - Generic Plugin
 *
 * Changes the loglevels during runtime.
 * Tested with cmn::tst::epics_now()
 * Usage example:
 *   dlog::Config::instance().init(level, timestamp_func);
 *   dlog::Print(dlog::INFO) << " debugvar " << debugvar;
 */

#include <iostream>
#include <functional>

namespace dlog
{
  enum Type
  {
    DEBUG3,
    DEBUG2,
    DEBUG1,
    DEBUG,
    INFO,
    WARNING,
    ERROR
  };
  class Config
  {
  public:
    Config();
    void init(dlog::Type *level, std::function<std::string()> timestamp, bool headers = true);
    static Config &instance();

  private:
    friend class Print;
    dlog::Type m_lv = INFO;
    dlog::Type *m_level = &m_lv;
    bool m_headers = true;
    std::function<std::string()> m_tstf;
  };

  class Print
  {
  public:
    Print(dlog::Type level = dlog::INFO);
    ~Print();
    template <typename T>
    Print &operator<<(const T &msg)
    {
      if (m_msglevel >= *m_config.m_level)
        std::cout << msg;

      return *this;
    };

  private:
    dlog::Config &m_config = dlog::Config::instance();
    dlog::Type m_msglevel;
  };

} // namespace dlog

#endif
