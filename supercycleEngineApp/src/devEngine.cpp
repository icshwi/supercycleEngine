#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "cmnbase.hpp"
#include "iocVars.hpp"
#include "ioblock.hpp"
#include "devStringoutCtrl.hpp"

static long initEngine()
{
    iocVars2IO();
    return 0;
}

int trig2mask(epicsUInt32 arg0, epicsUInt32 arg1, epicsUInt32 &mask)
{
    static epicsUInt32 trigNumSeq0 = 0, trigNumSeq1 = 0;

    if (trigNumSeq0 == arg0)
        mask = 0x00FF; // do seq0
    if (trigNumSeq1 == arg1)
        mask = 0xFF00; // do seq1

    trigNumSeq0 = arg0;
    trigNumSeq1 = arg1;

    return 0;
}

static long ioEngine(aSubRecord *prec)
{
    static io::IOBlock &io_block = io::RegisteredIOBlock();

    epicsUInt32 c_sel_mask = 0x00FF;
    trig2mask(*(epicsUInt32 *)prec->a, *(epicsUInt32 *)prec->b, c_sel_mask);

    // Configure new cycle
    io_block.dbSync(RegisteredStrOutMap);
    // Change the table if requested
    sctableSwitch(io_block);
    // Engine cycle
    engineCycle(io_block);
    // Update the meta
    epicsUInt64 *pvalaU64 = (epicsUInt64 *)prec->vala;
    epicsUInt32 *pvalaU32 = (epicsUInt32 *)prec->vala;
    pvalaU64[0] = io_block.cId; // 0,1
    pvalaU32[2] = (epicsUInt32)io_block.cPeriod;
    pvalaU32[3] = (epicsUInt32)c_sel_mask;
    // Update the Dbuf - neva , novb (max)
    prec->nevb = cmn::vec2p<epicsUInt32>(prec->valb, io_block.dbuf.vallist());
    prec->nevc = cmn::vec2p<epicsUInt32>(prec->valc, io_block.Seq.getSeqTst());
    prec->nevd = cmn::vec2p<epicsUInt32>(prec->vald, io_block.Seq.getSeqEvt());
    prec->neve = cmn::vec2p<epicsUInt32>(prec->vale, io_block.Seq.getSeqVec());

    return 0;
}

// Register the function
extern "C"
{
    epicsRegisterFunction(initEngine);
    epicsRegisterFunction(ioEngine);
}
