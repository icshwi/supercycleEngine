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
    std::string psce = "TD-M:TS-SCE-01:";
    std::string pevg = "MTCA5U-EVG:";

    std::string reftabs_TOP = "../../../reftabs/";
    std::string init_dbuf_json = "databuffer-ess.json";
    std::string init_mevts_json = "mevts-ess.json";

public:
    std::string sctable_csv = "example02.csv";
    epicsUInt32 sc_prd_us = 0; //sc engine period [us]
    std::string get_PSCE() { return psce; };
    std::string get_PEVG() { return pevg; };

    IOBlock();
    ~IOBlock();
    int init(int argc, char **argv);
    int init();

    std::string get_init_dbuf_json_link() { return (reftabs_TOP + "init/" + init_dbuf_json); };
    std::string get_init_mevts_json_link() { return (reftabs_TOP + "init/" + init_mevts_json); };
    std::string get_sctable_csv_link() { return (reftabs_TOP + "supercycles/" + sctable_csv); };

    io::JsonDBUF json_dbuf;
    io::JsonEVT json_evt;
    io::CSVReader sctable;
    // Set the send buffer
    dbf::DBufPacket dbuf;
    SequenceHandler SEQ;
};

} // namespace io

#endif // MENU_HPP_
