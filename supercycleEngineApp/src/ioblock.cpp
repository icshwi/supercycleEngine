
#include "ioblock.hpp"
#include "dlog.hpp"

#include <iostream>

#include "cmnbase.hpp"

using namespace std;

namespace io
{

IOBlock::~IOBlock()
{
    io::LOG(io::DEBUG) << "IOBlock::~IOBlock()";
    // Kill all not used processes
    SEVCHK(ca_task_exit(), "ERROR ca_task_exit failure");
}

IOBlock::IOBlock(int argc,char **argv)
:   json_dbuf(get_init_dbuf_json_link()),
    json_evt(get_init_mevts_json_link())
    //sctable(sctable_csv_strget())
{
    init(argc, argv);
}

IOBlock::IOBlock()
:   json_dbuf(get_init_dbuf_json_link()),
    json_evt(get_init_mevts_json_link())
    //sctable(sctable_csv_strget())
{
    init();
}

int
IOBlock::init(int argc,char **argv)
{
    io::LOG(io::DEBUG2) << "IOBlock::init() argc " << argc;

    cliargs=cmn::cli2map(argc, argv, keys);
    io::LOG(io::DEBUG2) << "IOBlock::init() cliargs[argv0] " << cliargs["argv0"];
    io::LOG(io::INFO) << "IOBlock::init() cmn::mapcol2str<std::string>(cliargs,0) " << cmn::mapcol2str<std::string>(cliargs,0);
    io::LOG(io::INFO) << "IOBlock::init() cmn::mapcol2str<std::string>(cliargs,1) " << cmn::mapcol2str<std::string>(cliargs,1);

    cmn::getMapVal(psce, "-e", cliargs);
    cmn::getMapVal(pevg, "-g", cliargs);
    cmn::getMapVal(init_dbuf_json, "-r", cliargs);

    // Subscribe to PVs
     //SCE
    IdCycleCa.init      (psce+"IdCycle");
    PeriodCa.init       (psce+"Period-I");

    TgRastCa.init       (psce+"TgRast");
    TgSegCa.init        (psce+"TgSeg");

    RefTabsTopCa.init   (psce+"RefTabsTop-SP");
    SCTableCa.init      (psce+"SCTable-SP");

     //EVG
    SoftEvtCa.init      (pevg+"SoftEvt-EvtCode-SP");
    DbusSendCa.init     (pevg+"dbus-send-u32");
    SEQ.init(pevg, json_evt.getEvtMap());

    // Init .db
    RefTabsTopCa.get(reftabs_TOP);
    SCTableCa.get(sctable_csv);

    io::LOG(io::INFO) << "IOBlock::init() psce " << psce << " pevg " << pevg;
    io::LOG(io::INFO) << "IOBlock::init() get_init_dbuf_json_link() "   << get_init_dbuf_json_link();
    io::LOG(io::INFO) << "IOBlock::init() get_init_mevts_json_link() "  << get_init_mevts_json_link();
    io::LOG(io::INFO) << "IOBlock::init() get_sctable_csv_link() "      << get_sctable_csv_link();
    return 0;
}


int
IOBlock::init()
{
    // Subscribe to PVs
     //SCE
    IdCycleCa.init      (psce+"IdCycle");
    PeriodCa.init       (psce+"Period-I");

    TgRastCa.init       (psce+"TgRast");
    TgSegCa.init        (psce+"TgSeg");

    RefTabsTopCa.init   (psce+"RefTabsTop-SP");
    SCTableCa.init      (psce+"SCTable-SP");

     //EVG
    SoftEvtCa.init      (pevg+"SoftEvt-EvtCode-SP");
    DbusSendCa.init     (pevg+"dbus-send-u32");
    SEQ.init(pevg, json_evt.getEvtMap());

    // Init .db
    RefTabsTopCa.get(reftabs_TOP);
    SCTableCa.get(sctable_csv);

    io::LOG(io::INFO) << "IOBlock::init() psce " << psce << " pevg " << pevg;
    io::LOG(io::INFO) << "IOBlock::init() get_init_dbuf_json_link() "   << get_init_dbuf_json_link();
    io::LOG(io::INFO) << "IOBlock::init() get_init_mevts_json_link() "  << get_init_mevts_json_link();
    io::LOG(io::INFO) << "IOBlock::init() get_sctable_csv_link() "      << get_sctable_csv_link();

    return 0;
}

}
