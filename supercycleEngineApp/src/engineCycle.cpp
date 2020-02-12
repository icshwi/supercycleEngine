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
    return engineStroke(io_block);
}

/* Note the function must be registered at the end!*/
epicsRegisterFunction(engineCycle);
