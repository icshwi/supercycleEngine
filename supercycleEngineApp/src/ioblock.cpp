
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
      json_evt(get_init_mevts_json_link()),
      sctable(get_SCTable_link())
{
    //init();
}

int IOBlock::init(std::map<std::string, std::string> argm)
{
    json_dbuf.init(get_init_dbuf_json_link());
    Seq.init(json_evt.getEvtMap());

    io::LOG(io::INFO) << "IOBlock::init() get_init_dbuf_json_link() " << get_init_dbuf_json_link();
    io::LOG(io::INFO) << "IOBlock::init() get_init_mevts_json_link() " << get_init_mevts_json_link();
    io::LOG(io::INFO) << "IOBlock::init() get_sctable_csv_link() " << get_SCTable_link();

    return 0;
}

int IOBlock::dbSync()
{

    for (auto const &it : dbCtrlArgs)
    {
        if (cmn::isSubstring(it.first, GETVARNAME(SCTable)))
            SCTable = it.second;
    }

    return 0;
}

} // namespace io
