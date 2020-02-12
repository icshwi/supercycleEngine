#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "dlog.hpp"

io::IOBlock io_block;

static uint64_t devEngineCycle(aSubRecord *prec)
{
    return engineCycle(io_block);
}

// Register the function
epicsRegisterFunction(devEngineCycle);
