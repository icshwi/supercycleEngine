#include <stdio.h>
//#include <subRecord.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <vector>
#include <stdint.h>

#include "ioblock.hpp"
extern io::IOBlock io_block;

#include "cmnbase.hpp"

static long initDbuf(aSubRecord *prec)
{
    //aSubRecord *prec = (aSubRecord *)pRecord;
    //prec->valu = &enabled;
    return 0;
}

static long ioDbuf(aSubRecord *prec)
{
    uint32_t *arr;
    std::vector<uint32_t> v;
    int i = 0;

    arr = (uint32_t *)prec->vala;
    v = io_block.dbuf.vallist();

    if (v.empty() == false)
    {
        for (uint32_t const &it : v)
        {
            arr[i] = it;
            i++;
        }
        //cmn::vec2stdio(v);
    }

    return i;
    //return 0 OUTA.. process output links
}

/*
static long ioDbuf(aSubRecord *prec)
{
    long i;
    uint32_t *arr;
    arr = (uint32_t *)prec->vala;
    for (i = 0; i < 5; i++)
    {
        arr[i] = i;
    }
    return 0; // process output links
}
*/

// Register the function

epicsRegisterFunction(initDbuf);
epicsRegisterFunction(ioDbuf);
