
#include "ioblock.hpp"
#include "dlog.hpp"

#include <iostream>

#include "cmnbase.hpp"

namespace io
{

IOBlock::~IOBlock()
{
    io::LOG(io::DEBUG) << "IOBlock::~IOBlock()";
    // Kill all not used processes
    // SEVCHK(ca_task_exit(), "ERROR ca_task_exit failure");
}

IOBlock::IOBlock()
    : json_dbuf(get_init_dbuf_json_link()),
      json_evt(get_init_mevts_json_link())
//sctable(sctable_csv_strget())
{
    init();
}

int IOBlock::init()
{
    // Subscribe to PVs
    //SCE
    //IdCycleCa.init      (psce+"IdCycle");
    //PeriodCa.init       (psce+"Period-I");

    //TgRastCa.init       (psce+"TgRast");
    //TgSegCa.init        (psce+"TgSeg");

    //RefTabsTopCa.init   (psce+"RefTabsTop-SP");
    //SCTableCa.init      (psce+"SCTable-SP");

    //EVG
    //SoftEvtCa.init      (pevg+"SoftEvt-EvtCode-SP");
    //DbusSendCa.init     (pevg+"dbus-send-u32");
    //SEQ.init(pevg, json_evt.getEvtMap());

    // Init .db
    //RefTabsTopCa.get(reftabs_TOP);
    //SCTableCa.get(sctable_csv);

    io::LOG(io::INFO) << "IOBlock::init() psce " << psce << " pevg " << pevg;
    io::LOG(io::INFO) << "IOBlock::init() get_init_dbuf_json_link() " << get_init_dbuf_json_link();
    io::LOG(io::INFO) << "IOBlock::init() get_init_mevts_json_link() " << get_init_mevts_json_link();
    io::LOG(io::INFO) << "IOBlock::init() get_sctable_csv_link() " << get_sctable_csv_link();

    return 0;
}

} // namespace io
