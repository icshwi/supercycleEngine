/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-07
 */

#include "dperf.hpp"
#include <iostream>
#include <iomanip>

namespace dperf
{
  Timer::Timer(std::string func_name, dperf::LevelTypes level) : _func_name(func_name), _level(level), _cfg_level(*dperf::Config::instance()._plevel)
  {
    if (_level >= _cfg_level)
      _start = std::chrono::high_resolution_clock::now();
  }

  Timer::~Timer()
  {
    if (_level >= _cfg_level)
      _stop();
  }

  void Timer::_stop()
  {
    _end = std::chrono::high_resolution_clock::now();
    _elasped = _end - _start;
    std::cout << _func_name << " level " << _level << " Timer::_elasped " << std::fixed << std::setprecision(9) << _elasped.count() << " us" << std::endl;
  }

  void Config::init(dperf::LevelTypes *const plevel)
  {
    _plevel = plevel;
  }

  Config &Config::instance()
  {
    static Config instance;
    return instance;
  }

} // namespace dperf
