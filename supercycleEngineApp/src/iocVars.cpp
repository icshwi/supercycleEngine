#include "iocVars.hpp"

#include "dlog.hpp"
#include <epicsExport.h>
#include "ioblock.hpp"

#include "iocsh.h"
//int and double only
static int iodebug = 4;
epicsExportAddress(int, iodebug);

void init_io_block()
{
    static io::LOGCONFIG &LOGCFG = io::RegistrarLOGCFG();

    static io::typelog *const piodebug = (io::typelog *)&iodebug;
    LOGCFG.init(true, piodebug);

    //io_block.init(reftabs_TOP);
    //io_block.reftabs_TOP(reftabs_TOP);
}
