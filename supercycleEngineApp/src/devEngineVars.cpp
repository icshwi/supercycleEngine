#include "devEngineVars.hpp"

#include "dlog.hpp"
#include <epicsExport.h>
#include "ioblock.hpp"

static int iodebug = 4;
epicsExportAddress(int, iodebug);

static io::typelog *const piodebug = (io::typelog *)&iodebug;
io::structlog io::LOGCFG(true, piodebug);
