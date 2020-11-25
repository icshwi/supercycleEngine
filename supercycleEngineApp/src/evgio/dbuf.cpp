/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

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

    DBufPacket::DBufPacket(epicsUInt32 size)
    {
        dlog::Print(dlog::DEBUG2) << "DBufPacket::DBufPacket()";
        assert((sizeof(size) == 4) && "The databuffer requires 4 byte uint");
        for (size_t i = 0; i < (size * 4); i += 4)
        {
            dbuf[i] = 0;
        }
    }

    DBufPacket::~DBufPacket()
    {
        dlog::Print(dlog::DEBUG2) << "DBufPacket::~DBufPacket()";
        dbuf.clear();
    }

    int DBufPacket::clear()
    {
        dlog::Print(dlog::DEBUG2) << "DBufPacket::clear()";

        for (size_t i = 0; i < (dbuf.size() * 4); i += 4)
        {
            dbuf[i] = 0;
        }

        return 0;
    }

    int DBufPacket::write(epicsUInt32 idx, epicsUInt32 val)
    {
        epicsUInt32 idx_shift, idx_base;
        dlog::Print(dlog::DEBUG2) << "DBufPacket::write()";

        if (idx >= size_byte())
        {
            dlog::Print(dlog::ERROR) << "DBufPacket::write idx oversized, size_byte() " << size_byte() << " idx " << idx;
            return 1;
        }

        idx_shift = idx % 4;
        idx_base = epicsUInt32(idx / 4) * 4;

        //Clear the dbuf int field if it is the new entry
        if (idx_shift == 0)
            dbuf[idx_base] = 0;

        dbuf[idx_base] = epicsUInt32((dbuf[idx_base] | (val << (idx_shift * dbuf.size()))) & 0xFFFFFFFF);

        dlog::Print(dlog::DEBUG1) << "DBufPacket::write "
                                  << "idx_base " << idx_base << " idx_shift " << idx_shift << " dbuf[idx_base] " << dbuf[idx_base];

        return 0;
    }

    int DBufPacket::read(epicsUInt32 idx)
    {
        return dbuf[idx];
    }

    size_t DBufPacket::size()
    {
        return dbuf.size();
    }

    size_t DBufPacket::size_byte()
    {
        return dbuf.size() * sizeof(dbuf[0]);
    }

    std::vector<epicsUInt32> DBufPacket::keylist()
    {
        return cmn::map1d2vec<epicsUInt32>(dbuf, 0);
    }

    std::vector<epicsUInt32> DBufPacket::vallist()
    {
        return cmn::map1d2vec<epicsUInt32>(dbuf, 1);
    }

} // namespace dbf
