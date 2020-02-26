#ifndef DLOG_HPP_
#define DLOG_HPP_

//Super Simple Log Plugin

#include <iostream>
#include "cmnbase.hpp"

namespace io
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

class LOGCONFIG
{
public:
    bool headers = true;
    typelog lv = INFO;
    typelog *level = &lv;

    LOGCONFIG() { ; };
    LOGCONFIG(bool hdr, typelog *lvl)
    {
        init(hdr, lvl);
    };
    void init(bool hdr, typelog *lvl)
    {
        headers = hdr;
        level = lvl;
    };
};

LOGCONFIG &RegisteredLOGCFG();

class LOG
{
public:
    LOG() { ; };
    LOG(typelog type)
    {
        msglevel = type;
        if (LOGCFG.headers && (msglevel >= *LOGCFG.level))
        {
            operator<<(cmn::epicssTstSysNow() + " " + getLabel(type) + " ");
        }
    };
    ~LOG()
    {
        if (opened && (msglevel >= *LOGCFG.level))
        {
            std::cout << std::endl;
        }
        opened = false;
    };
    template <class T>
    LOG &operator<<(const T &msg)
    {
        if (msglevel >= *LOGCFG.level)
        {
            std::cout << msg;
            opened = true;
        }
        return *this;
    };

private:
    LOGCONFIG &LOGCFG = RegisteredLOGCFG();
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

} // namespace io

#endif /* DLOG_HPP */
