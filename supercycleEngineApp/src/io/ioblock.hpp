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

namespace io
{

class IOBlock
{
public:
  IOBlock(){};
  //int init(int argc, char **argv);
  int init();

  mutable epicsUInt32 cPeriod = 0; //cycle period [us]
  mutable epicsUInt64 cId = 0;

  io::YmlDatabuffer DBuf_yml;
  io::YmlSCEConfig SCEConfig_yml;
  io::YmlMEvts mEvts_yml;
  sce::csv::FileReader CSVReader;
  // Set the send buffer
  sce::DBufPacket dbuf;
  sce::SequenceHandler Seq;
};

IOBlock& RegisteredIOBlock();

#define REGIO io::RegisteredIOBlock()

} // namespace io

#endif // MENU_HPP_
