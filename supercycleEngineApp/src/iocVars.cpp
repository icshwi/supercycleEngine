#include "iocVars.hpp"

#include "dlog.hpp"
#include <epicsExport.h>
#include "ioblock.hpp"

#include "iocsh.h"
//int and double only
static int iodebug = 4;
epicsExportAddress(int, iodebug);

static io::typelog *const piodebug = (io::typelog *)&iodebug;
io::structlog io::LOGCFG(true, piodebug);

extern io::IOBlock io_block;

void init_io_block()
{
    //io_block.init(reftabs_TOP);
    //io_block.reftabs_TOP(reftabs_TOP);
}
