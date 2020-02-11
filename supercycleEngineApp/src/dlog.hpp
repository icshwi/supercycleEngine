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

struct structlog
{
    bool headers;
    typelog level;

public:
    structlog(bool hdr, typelog lvl)
    {
        headers = hdr;
        level = lvl;
    }
};

extern structlog LOGCFG;

class LOG
{
public:
    LOG() {}
    LOG(typelog type)
    {
        msglevel = type;
        if (LOGCFG.headers && (msglevel >= LOGCFG.level))
        {
            operator<<(cmn::timestamp() + " " + getLabel(type) + " ");
        }
    }
    ~LOG()
    {
        if (opened && (msglevel >= LOGCFG.level))
        {
            std::cout << std::endl;
        }
        opened = false;
    }
    template <class T>
    LOG &operator<<(const T &msg)
    {
        if (msglevel >= LOGCFG.level)
        {
            std::cout << msg;
            opened = true;
        }
        return *this;
    }

private:
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
    }
};

} // namespace io

#endif /* DLOG_HPP */
