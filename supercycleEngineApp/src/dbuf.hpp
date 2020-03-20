/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef DBUF_HPP
#define DBUF_HPP

#include <map>
#include <vector>
#include <epicsTypes.h>

namespace dbf
{

class DBufPacket
{
public:
    //DataBuffer();
    DBufPacket(epicsUInt32 size = 8);
    ~DBufPacket();
    int write(epicsUInt32 idx, epicsUInt32 val);
    int read(epicsUInt32 idx);
    int clear();
    size_t size();
    size_t size_byte();
    std::vector<epicsUInt32> keylist();
    std::vector<epicsUInt32> vallist();
    std::map<epicsUInt32, epicsUInt32> getDbuf() { return dbuf; };

private:
    std::map<epicsUInt32, epicsUInt32> dbuf;
};

//void demo1();

} // namespace dbf

#endif // DBUF_HPP
