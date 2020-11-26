/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef DLOG_HPP_
#define DLOG_HPP_

//Super Simple Log Plugin
#define DLOG_TST_NOW cmn::tst::epics_now()
#include "cmnbase.hpp"

#include <iostream>

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

    Config(){};
    Config(bool hdr, dlog::Type *lvl);
    void init(bool hdr, dlog::Type *lvl);
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
