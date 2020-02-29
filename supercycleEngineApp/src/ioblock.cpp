
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

int IOBlock::init(std::map<std::string, std::string> argm)
{
    if (cmn::isFile(argm[GETVARNAME(databufferLink)]))
        databufferLink = argm[GETVARNAME(databufferLink)];

    if (cmn::isFile(argm[GETVARNAME(mevtsLink)]))
        mevtsLink = argm[GETVARNAME(mevtsLink)];

    if (cmn::isFile(argm[GETVARNAME(sctableRoot)]))
        sctableRoot = argm[GETVARNAME(sctableRoot)];

    json_dbuf.init(databufferLink);
    json_evt.init(mevtsLink);
    sctable.init(get_SCTableLink());
    Seq.init(json_evt.getEvtMap());

    io::LOG(io::INFO) << "IOBlock::init() databufferLink " << databufferLink;
    io::LOG(io::INFO) << "IOBlock::init() mevtsLink " << mevtsLink;
    io::LOG(io::INFO) << "IOBlock::init() get_SCTableLink() " << get_SCTableLink();

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
