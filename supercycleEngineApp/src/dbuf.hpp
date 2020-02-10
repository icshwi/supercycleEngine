
#ifndef DBUF_HPP
#define DBUF_HPP

#include <map>
#include <vector>
#include "cach.hpp"

namespace dbf
{

class DBufPacket{
    public:
        //DataBuffer();
        DBufPacket(uint32_t size=8);
        ~DBufPacket();
        int write(uint32_t idx, uint32_t val);
        int read(uint32_t idx);
        int clear();
        int size();
        std::vector<uint32_t> keylist();
        std::vector<uint32_t> vallist();
        std::map<uint32_t,uint32_t> getDbuf(){return dbuf;};
    private:
        std::map<uint32_t,uint32_t> dbuf;
};

//void demo1();

} //namespace

#endif // DBUF_HPP
