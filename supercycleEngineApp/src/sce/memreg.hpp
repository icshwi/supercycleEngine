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
#include "scenv.hpp"
#include "seq.hpp"
#include "version.h"
#include "yml.hpp"

#include "epicsTypes.h"

namespace mem
{

class ScERegistry
{
public:
  ScERegistry(){};
  //int init(int argc, char **argv);
  int init();

  mutable epicsUInt32 cPeriod = 0; //cycle period [us]
  mutable epicsUInt64 cId = 0;

  sce::YmlDatabuffer DBuf;
  sce::YmlSCEConfig Config;
  sce::YmlMEvts MEvts;
  sce::csv::FileReader CSVHandler;
  // Set the send buffer
  sce::DBufPacket DBufHandler;
  sce::SequenceHandler SeqHandler;
};

ScERegistry& RegisteredIOBlock();

#define SCEMEMREG mem::RegisteredIOBlock()

} // namespace mem

#endif // MENU_HPP_
