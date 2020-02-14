#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"

static io::IOBlock io_block;

static long InitEngineASub(aSubRecord *pRecord)
{
    //aSubRecord *prec = (aSubRecord *)pRecord;
    //prec->valu = &enabled;
    return 0;
}

static uint64_t ProcEngineASub(aSubRecord *prec)
{
    return engineCycle(io_block);
}

// Register the function

epicsRegisterFunction(InitEngineASub);
epicsRegisterFunction(ProcEngineASub);
