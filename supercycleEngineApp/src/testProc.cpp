#include <stdio.h>
#include <subRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "engine.hpp"
#include "ioblock.hpp"
#include "dlog.hpp"

static int testProc(subRecord *precord)
{

    io::IOBlock io_block;

    precord->val++;
    engineCycle(io_block);
    io::LOG(io::DEBUG) << "static int testProc(subRecord *precord)";
    //std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" <<std::endl;

    return 0;
}

/* Note the function must be registered at the end!*/
epicsRegisterFunction(testProc);
