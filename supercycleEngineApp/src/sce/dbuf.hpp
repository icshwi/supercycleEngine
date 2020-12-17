/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef DBUF_HPP
#define DBUF_HPP

#include <epicsTypes.h>
#include <map>
#include <vector>

namespace sce
{

class DBufPacket
{
public:
  //DataBuffer();
  DBufPacket(epicsUInt32 size = 8);
  ~DBufPacket();
  int clear();
  int write(epicsUInt32 idx, epicsUInt32 val);
  std::vector<epicsUInt32> getKeys() const;
  std::vector<epicsUInt32> getVals() const;
  std::map<epicsUInt32, epicsUInt32> getDbuf() const { return dbuf; };

protected:
  int read(epicsUInt32 idx);
  size_t size() const;
  size_t size_byte() const;

private:
  std::map<epicsUInt32, epicsUInt32> dbuf;
};

//void demo1();

} // namespace sce

#endif // DBUF_HPP
