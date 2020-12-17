/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <map>
#include <string>

#include "cmdMapStrOut.hpp"
#include "csv.hpp"
#include "dbuf.hpp"
#include "seq.hpp"
#include "version.h"
#include "yml.hpp"

#include "epicsTypes.h"

namespace sce
{

class ScERegistry
{
private:
  //mutable epicsUInt64 _id = (epicsUInt64)round(cmn::tst::sec_now() / ScPeriodUs * 1000000);
  mutable epicsUInt64 _id = 0;
  mutable epicsUInt32 _period = 0; //cycle period [us]

public:
  ScERegistry(){};
  //int init(int argc, char **argv);
  int init();
  void initId(epicsUInt64 id) { _id = id; };
  void incId() const { ++_id; };
  epicsUInt64 getId() const { return _id; };
  void putPeriod(epicsUInt32 period) const { _period = period; };
  epicsUInt32 getPeriod() const { return _period; };

  sce::YmlDatabuffer DBuf;
  sce::YmlSCEConfig Config;
  sce::YmlMEvts MEvts;
  sce::csv::FileReader CSVHandler;
  // Set the send buffer
  sce::DBufPacket DBufHandler;
  sce::SequenceHandler SeqHandler;
};

ScERegistry& RegisteredIOBlock();

#define SCEMEMREG sce::RegisteredIOBlock()

} // namespace sce

#endif // MENU_HPP_
