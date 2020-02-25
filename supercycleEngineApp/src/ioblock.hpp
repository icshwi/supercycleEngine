#ifndef MENU_HPP_
#define MENU_HPP_

#include <string>
#include <map>

#include "scenv.hpp"
#include "dbuf.hpp"
#include "json.hpp"
#include "csv.hpp"
#include "seq.hpp"

#include "epicsTypes.h"

namespace io
{

class IOBlock
{
private:
    std::string init_dbuf_json = "databuffer-ess.json";
    std::string init_mevts_json = "mevts-ess.json";
    std::string reftabs_TOP = "../../../reftabs/";
    std::string SCTable = "null.csv";

public:
    IOBlock();
    ~IOBlock();
    //int init(int argc, char **argv);
    int init();

    epicsUInt32 cPeriod = 0;     //cycle period [us]
    epicsUInt32 cOffset = 30000; //[us]
    epicsUInt64 cId = (epicsUInt64)round((cmn::epicssTstSysNowSec() - EPICS2020s) * CYCLE_fHz);

    std::string get_init_dbuf_json_link() { return (reftabs_TOP + "init/" + init_dbuf_json); };
    std::string get_init_mevts_json_link() { return (reftabs_TOP + "init/" + init_mevts_json); };
    std::string get_SCTable_link() { return (reftabs_TOP + "supercycles/" + SCTable); };

    io::JsonDBUF json_dbuf;
    io::JsonEVT json_evt;
    io::CSVReader sctable;
    // Set the send buffer
    dbf::DBufPacket dbuf;
    SequenceHandler Seq;

    std::map<std::string, std::string> dbCtrlArgs;
    int dbSync();
};

} // namespace io

#endif // MENU_HPP_
