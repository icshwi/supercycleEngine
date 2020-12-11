/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <map>
#include <string>

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
private:
  // Links
  std::string databufferLink = "/opt/reftabs/init/databuffer-ess.yml";
  std::string mevtsLink = "/opt/reftabs/init/mevts-ess.yml";
  std::string sceconfigLink = "/opt/reftabs/init/sceconfig-ess.yml";
  // Directories
  std::string sctableRoot = "/opt/reftabs/supercycles/";
  // PVs
  std::string SCTable = "null.csv";
  std::string PBState = "Off";
  std::string PBMod = "None";
  std::string PBDest = "None";

public:
  IOBlock(){};
  //int init(int argc, char **argv);
  int init(std::map<std::string, std::string>);
  std::string getSCTableLink() const { return (sctableRoot + SCTable); };
  std::string getPBState() const { return PBState; };
  std::string getPBMod() const { return PBMod; };
  std::string getPBDest() const { return PBDest; };

  mutable epicsUInt32 cPeriod = 0; //cycle period [us]
  mutable epicsUInt64 cId = 0;

  io::YmlDatabuffer DBuf_yml;
  io::YmlSCEConfig SCEConfig_yml;
  io::YmlMEvts mEvts_yml;
  io::CSVStrMap CSVTab;
  // Set the send buffer
  sce::DBufPacket dbuf;
  sce::SequenceHandler Seq;

  int dbSync(const std::map<std::string, std::string>&);
};

IOBlock& RegisteredIOBlock();

} // namespace io

#endif // MENU_HPP_
