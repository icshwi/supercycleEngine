#include "iocVars.hpp"

#include "dlog.hpp"
#include <epicsExport.h>
#include "ioblock.hpp"

#include "iocsh.h"
#include "cmdMapStrOut.hpp"
//int and double only
static int iodebug = 4;
epicsExportAddress(int, iodebug);

static int PscUs = 71428; //[us]
epicsExportAddress(int, PscUs);

void iocVars2IO()
{
    static io::LOGCONFIG &LOGCFG = io::RegisteredLOGCFG();
    static io::IOBlock &io_block = io::RegisteredIOBlock();

    static io::typelog *const piodebug = (io::typelog *)&iodebug;
    LOGCFG.init(true, piodebug);

    io_block.cId = (epicsUInt64)round((cmn::epicssTstSysNowSec() - EPICS2020s) / PscUs * 1000000);
    io_block.init(RegisteredCmdMapStrOut);

    io::LOG(io::INFO) << "iocVars2IO() iodebug " << iodebug << " PscUs " << PscUs;
}
