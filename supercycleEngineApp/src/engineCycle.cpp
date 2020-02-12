#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "dlog.hpp"

io::IOBlock io_block;

static uint64_t engineCycle(aSubRecord *prec)
{
    uint64_t id_cycle = engineStroke(io_block);
    return id_cycle; /* process output links */
}

/* Note the function must be registered at the end!*/
epicsRegisterFunction(engineCycle);
