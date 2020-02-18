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
    uint64_t *pvala64 = (uint64_t *)prec->vala;
    uint32_t *pvala32 = (uint32_t *)prec->vala;

    pvala64[0] = IdCycle;
    pvala32[2] = (uint32_t)io_block.sc_prd_us;
    pvala32[3] = (uint32_t)env::DATAS;

    // Update the Dbuf
    prec->novb = cmn::vec2p(io_block.dbuf.vallist(), (uint32_t *)prec->valb);
    // Update the sequence
    prec->novc = cmn::vec2p(io_block.SEQ.getSeqTst(), (uint32_t *)prec->valc);
    prec->novd = cmn::vec2p(io_block.SEQ.getSeqEvt(), (uint32_t *)prec->vald);

    return 0;
}

// Register the function

epicsRegisterFunction(initEngine);
epicsRegisterFunction(ioEngine);
