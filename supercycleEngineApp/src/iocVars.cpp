#include "iocVars.hpp"

#include "dlog.hpp"
#include <epicsExport.h>
#include "ioblock.hpp"

#include "iocsh.h"
#include "cmdMapStrOut.hpp"
//int and double only
static int iodebug = 4;
epicsExportAddress(int, iodebug);

void iocVars2IO()
{
    static io::LOGCONFIG &LOGCFG = io::RegisteredLOGCFG();
    static io::IOBlock &io_block = io::RegisteredIOBlock();

    static io::typelog *const piodebug = (io::typelog *)&iodebug;
    LOGCFG.init(true, piodebug);

    io_block.init(RegisteredCmdMapStrOut);
    //io_block.init(reftabs_TOP);
    //io_block.reftabs_TOP(reftabs_TOP);
}
