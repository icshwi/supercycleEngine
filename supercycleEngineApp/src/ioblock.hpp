#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <map>
#include <scenv.hpp>
#include "cach.hpp"
#include "dbuf.hpp"
#include "json.hpp"
#include "csv.hpp"
#include "sequence.hpp"

namespace io
{

class IOBlock
{
    private:
        uint EC_INHIBIT=30000; // [us] Block the engine cycles over this time
        std::string psce = "TD-M:TS-SCE-01:";
        std::string pevg = "MTCA5U-EVG:";

        std::string reftabs_TOP     = "../reftabs/";
        std::string init_dbuf_json  = "databuffer-ess.json";
        std::string init_mevts_json = "mevts-ess.json";

    public:
        std::string sctable_csv     = "example02.csv";
        uint get_ECInhibit(){return EC_INHIBIT;};
        std::string get_PSCE(){return psce;};
        std::string get_PEVG(){return pevg;};
        // Hidden keys:
            // * "b": filename execution string
        // Parameters
            // -e psce, -g pevg, -r initjsonref, -s sctableref
        std::vector<std::string> keys = {"-e", "-g", "-r"};
        std::map<std::string, std::string> cliargs;
        IOBlock(int argc,char **argv);
        ~IOBlock();
        int init(int argc,char **argv);

        std::string get_init_dbuf_json_link(){return  (reftabs_TOP + "init/"        + init_dbuf_json);};
        std::string get_init_mevts_json_link(){return (reftabs_TOP + "init/"        + init_mevts_json);};
        std::string get_sctable_csv_link(){return     (reftabs_TOP + "supercycles/" + sctable_csv);};

        io::JsonDBUF json_dbuf;
        io::JsonEVT json_evt;
        io::CSVReader sctable;
        // Set the send buffer
        dbf::DBufPacket dbuf;

        // Program parameters
        CACh TgRastCa,TgSegCa,IdCycleCa,SoftEvtCa,DbusSendCa,PeriodCa;
        CACh SCTableCa, RefTabsTopCa;

        SequenceHandler SEQ;
};

} //namespace

#endif // MENU_HPP
