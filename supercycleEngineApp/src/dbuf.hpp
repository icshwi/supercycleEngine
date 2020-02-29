
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
    int size();
    int size_byte();
    std::vector<epicsUInt32> keylist();
    std::vector<epicsUInt32> vallist();
    std::map<epicsUInt32, epicsUInt32> getDbuf() { return dbuf; };

private:
    std::map<epicsUInt32, epicsUInt32> dbuf;
};

//void demo1();

} // namespace dbf

#endif // DBUF_HPP
