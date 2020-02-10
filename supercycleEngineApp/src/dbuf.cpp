#include "dbuf.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

// System
#include <iostream>
#include <map>
#include <string>
#include <assert.h>

namespace dbf
{

DBufPacket::DBufPacket(uint32_t size)
{
    io::LOG(io::DEBUG2) << "DBufPacket::DBufPacket()";
    assert((sizeof(size) == 4) && "The databuffer requires 4 byte uint");
    for (uint32_t i=0; i<(size*4); i+=4)
    {
        dbuf[i] = 0;
    }
}

DBufPacket::~DBufPacket()
{
    io::LOG(io::DEBUG2) << "DBufPacket::~DBufPacket()";
    dbuf.clear();
}

int DBufPacket::clear()
{
    io::LOG(io::DEBUG2) << "DBufPacket::clear()";

    for (uint32_t i=0; i<(dbuf.size()*4); i+=4)
    {
        dbuf[i] = 0;
    }

return 0;
}

int DBufPacket::write(uint32_t idx, uint32_t val)
{
    uint32_t idx_shift, idx_base;
    io::LOG(io::DEBUG2) << "DBufPacket::write()";

    idx_shift = idx % 4;
    idx_base = uint32_t(idx/4) * 4;

    //Clear the dbuf int field if it is the new entry
    if (idx_shift == 0) dbuf[idx_base]=0;

    dbuf[idx_base] = uint32_t( ( dbuf[idx_base] | (val << (idx_shift * dbuf.size())) ) & 0xFFFFFFFF);

    io::LOG(io::DEBUG1) << "DBufPacket::write " << "idx_base " << idx_base << " idx_shift " << idx_shift << " dbuf[idx_base] " << dbuf[idx_base];

    return 0;
}

int DBufPacket::read(uint32_t idx)
{
    return dbuf[idx];
}

int DBufPacket::size()
{
    return dbuf.size();
}

std::vector<uint> DBufPacket::keylist()
{
    return cmn::map2vec<uint>(dbuf, 0);
}

std::vector<uint> DBufPacket::vallist()
{
    return cmn::map2vec<uint>(dbuf, 1);
}


} //namespace

