#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <iostream>

static long InitDbufASub(aSubRecord *pRecord)
{
    //aSubRecord *prec = (aSubRecord *)pRecord;
    //prec->valu = &enabled;
    return 0;
}

static long ProcDbufASub(aSubRecord *prec)
{
    std::cout << "ProcDbufASub" << std::endl;
    return 10;
    //return engineCycle(io_block);
}

// Register the function

epicsRegisterFunction(InitDbufASub);
epicsRegisterFunction(ProcDbufASub);
