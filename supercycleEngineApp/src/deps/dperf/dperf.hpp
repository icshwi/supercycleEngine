/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-07
 */

#pragma once

#include <chrono>
#include <string>

#define DPERFTIMERSCOPE(level) dperf::Timer timer_(__PRETTY_FUNCTION__, level)
namespace dperf
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
  Config(){};
  void init(dperf::LevelTypes* const plevel);
  static Config& instance();

private:
  friend class Timer;
  dperf::LevelTypes _level = dperf::INFO;
  dperf::LevelTypes* _plevel = &_level;
};

class Timer
{
public:
  Timer(const std::string& func_name, dperf::LevelTypes level);
  ~Timer();

private:
  void _stop();
  std::chrono::time_point<std::chrono::high_resolution_clock> _start, _end;
  std::chrono::duration<double> _elasped;
  std::string _func_name;
  dperf::LevelTypes _level;
  dperf::LevelTypes _cfg_level;
};

} // namespace dperf
