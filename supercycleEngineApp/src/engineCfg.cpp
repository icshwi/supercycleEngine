#include "dlog.hpp"
#include <epicsExport.h>

static int iodebug = 4;
epicsExportAddress(int, iodebug);

static io::typelog *const piodebug = (io::typelog *)&iodebug;
io::structlog io::LOGCFG(true, piodebug);
