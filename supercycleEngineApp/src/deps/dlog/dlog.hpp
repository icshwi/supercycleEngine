/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#pragma once

/**
 * Debug Log - Generic Plugin
 *
 * Changes the loglevels during runtime.
 * Tested with cmn::tst::epics_now()
 * Usage example:
 *   init: dlog::Config::instance().init(level, timestamp_func);
 *   body: DLOG(lv, stream)
 */

#include <functional>
#include <iostream>

#define DBGLOG_

#if defined DBGLOG_
#  if defined __COMPACT_PRETTY_FUNCTION__
#    define DLOG(lv, stream) dlog::Print(lv) << __COMPACT_PRETTY_FUNCTION__ stream;
#  else
#    define DLOG(lv, stream) dlog::Print(lv) stream;
#  endif
#else
#  define DLOG(lv, stream)
#endif
namespace dlog
{
enum LevelTypes
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
  void init(dlog::LevelTypes* level, std::function<std::string()> timestamp);
  static Config& instance();

private:
  friend class Print;
  dlog::LevelTypes _level = INFO;
  dlog::LevelTypes* _plevel = &_level;
  std::function<std::string()> _tstf;
};

class Print
{
public:
  Print(dlog::LevelTypes level = dlog::INFO);
  ~Print();

  template <typename T>
  Print& operator<<(const T& msg)
  {
    if (_msglevel >= _cfg_level)
      std::cout << msg;

    return *this;
  };

private:
  dlog::LevelTypes _msglevel;
  dlog::LevelTypes _cfg_level;
};

} // namespace dlog
