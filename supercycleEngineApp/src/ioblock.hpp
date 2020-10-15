/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <string>
#include <map>

#include "scenv.hpp"
#include "dbuf.hpp"
#include "json.hpp"
#include "csv.hpp"
#include "seq.hpp"
#include "yml.hpp"

#include "epicsTypes.h"

namespace io
{

  class IOBlock
  {
  private:
    std::string databufferLink = "../reftabs/init/databuffer-ess.json";
    std::string mevtsLink = "../reftabs/init/mevts-ess.json";
    std::string sctableRoot = "../reftabs/supercycles/";
    std::string SCTable = "example02.csv";

  public:
    IOBlock(){};
    ~IOBlock();
    //int init(int argc, char **argv);
    int init(std::map<std::string, std::string>);
    std::string get_SCTableLink() { return sctableRoot + SCTable; };

    epicsUInt32 cPeriod = 0; //cycle period [us]
    epicsUInt64 cId = 0;

    io::JsonDBUF json_dbuf;
    io::JsonEVT json_evt;
    io::CSVReader sctable;
    // Set the send buffer
    dbf::DBufPacket dbuf;
    SequenceHandler Seq;

    int dbSync(std::map<std::string, std::string> &);
  };

  IOBlock &RegisteredIOBlock();

} // namespace io

#endif // MENU_HPP_
