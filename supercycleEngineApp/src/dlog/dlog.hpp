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
  private:
    dlog::Type lv = INFO;

  public:
    bool headers = true;
    dlog::Type *level = &lv;
    std::function<std::string()> tstf;

    Config();
    void init(dlog::Type *level_switch, std::function<std::string()> timestamp, bool headers = true);
    static Config &instance();
  };

  class Print
  {
  public:
    Print(dlog::Type type = dlog::INFO);
    ~Print();
    template <typename T>
    Print &operator<<(const T &msg)
    {
      if (msglevel >= *config.level)
      {
        std::cout << msg;
        opened = true;
      }
      return *this;
    };

  private:
    bool opened;
    dlog::Config &config = dlog::Config::instance();
    dlog::Type msglevel;
  };

} // namespace dlog

#endif
