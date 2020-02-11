#include <stdio.h>
#include <subRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "dlog.hpp"

io::IOBlock io_block;

static int engineCycle(subRecord *precord)
{
    //precord->val++;
    precord->val = engineStroke(io_block);
    return 0;
}

/* Note the function must be registered at the end!*/
epicsRegisterFunction(engineCycle);
