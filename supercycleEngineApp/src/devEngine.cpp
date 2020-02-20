#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "cmnbase.hpp"

extern io::IOBlock io_block;

//static long initEngine(aSubRecord *pRecord)
//{
//    //aSubRecord *prec = (aSubRecord *)pRecord;
//    //prec->valu = &enabled;
//    return 0;
//}

static long ioEngine(aSubRecord *prec)
{
    static uint32_t dmux_sel = 0;

    uint64_t IdCycle = engineCycle(io_block);
    // Update the meta
    uint64_t *pvala64 = (uint64_t *)prec->vala;
    uint32_t *pvala32 = (uint32_t *)prec->vala;

    pvala64[0] = IdCycle; // 0,1
    pvala32[2] = (uint32_t)io_block.sc_prd_us;
    pvala32[3] = (uint32_t)env::DATAS;
    pvala32[4] = !dmux_sel; // 0 means active seq0
    pvala32[5] = dmux_sel;  // 1 means active seq1

    // Update the Dbuf
    // neva , novb (max)
    prec->nevb = cmn::vec2p(io_block.dbuf.vallist(), (uint32_t *)prec->valb);

    switch (dmux_sel)
    {
    case 0:
        // Update the sequence 0
        prec->nevc = cmn::vec2p(io_block.SEQ.getSeqTst(), (uint32_t *)prec->valc);
        prec->nevd = cmn::vec2p(io_block.SEQ.getSeqEvt(), (uint32_t *)prec->vald);
        break;
    case 1:
        // Update the sequence 1
        prec->neve = cmn::vec2p(io_block.SEQ.getSeqTst(), (uint32_t *)prec->vale);
        prec->nevf = cmn::vec2p(io_block.SEQ.getSeqEvt(), (uint32_t *)prec->valf);
        break;
    default:
        break;
    }
    dmux_sel = !dmux_sel;

    return 0;
}

// Register the function

//epicsRegisterFunction(initEngine);
epicsRegisterFunction(ioEngine);
