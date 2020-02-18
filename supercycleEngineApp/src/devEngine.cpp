#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "cmnbase.hpp"

extern io::IOBlock io_block;

static long initEngine(aSubRecord *pRecord)
{
    //aSubRecord *prec = (aSubRecord *)pRecord;
    //prec->valu = &enabled;
    return 0;
}

static uint64_t ioEngine(aSubRecord *prec)
{
    uint64_t IdCycle = engineCycle(io_block);

    // Update the meta
    uint32_t *pvala = (uint32_t *)prec->vala;
    pvala[0] = (uint32_t)io_block.sc_prd_us;

    // Update the Dbuf
    prec->novb = cmn::vec2p(io_block.dbuf.vallist(), (uint32_t *)prec->valb);
    return IdCycle;
}

// Register the function

epicsRegisterFunction(initEngine);
epicsRegisterFunction(ioEngine);
