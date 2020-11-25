/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef DLOG_HPP_
#define DLOG_HPP_

//Super Simple Log Plugin
#define TST_NOW cmn::tst::epics_now()
#include "cmnbase.hpp"

#include <iostream>

namespace dlog
{
  enum typelog
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
    bool headers = true;
    typelog lv = INFO;
    typelog *level = &lv;

    Config() { ; };
    Config(bool hdr, typelog *lvl)
    {
      init(hdr, lvl);
    };

    static Config &instance()
    {
      static Config instance;
      return instance;
    }

    void init(bool hdr, typelog *lvl)
    {
      headers = hdr;
      level = lvl;
    };
  };

  class Print
  {
  public:
    Print() { ; };
    Print(typelog type)
    {
      msglevel = type;
      if (LOGCFG.headers && (msglevel >= *LOGCFG.level))
      {
        operator<<(TST_NOW + " " + getLabel(type) + " ");
      }
    };
    ~Print()
    {
      if (opened && (msglevel >= *LOGCFG.level))
      {
        std::cout << std::endl;
      }
      opened = false;
    };
    template <class T>
    Print &operator<<(const T &msg)
    {
      if (msglevel >= *LOGCFG.level)
      {
        std::cout << msg;
        opened = true;
      }
      return *this;
    };

  private:
    dlog::Config &LOGCFG = dlog::Config::instance();
    bool opened;
    typelog msglevel;
    inline std::string getLabel(typelog type)
    {
      std::string label;
      switch (type)
      {
      case DEBUG3:
        label = "DEBUG2";
        break;
      case DEBUG2:
        label = "DEBUG2";
        break;
      case DEBUG1:
        label = "DEBUG1";
        break;
      case DEBUG:
        label = "DEBUG";
        break;
      case INFO:
        label = "INFO";
        break;
      case WARNING:
        label = "WARNING";
        break;
      case ERROR:
        label = "ERROR";
        break;
      }
      return label;
    };
  };

} // namespace dlog

#endif
