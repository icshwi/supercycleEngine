#include <stdlib.h>
#include <dbAccess.h>
#include <devSup.h>
#include <recGbl.h>
#include <alarm.h>

//#include <aiRecord.h>
//#include <longinRecord.h>
#include <stringoutRecord.h>

#include "devext.h"
#include <iostream>

static long initStrOutCtrl()
{
    return 0;
}

static long ioStrOutCtrl(stringoutRecord *prec)
{
    //struct devPriv *priv = prec->dpvt;
    //prec->val = (epicsInt32)sc_prd_us;
    std::string tmp1(prec->val);
    std::cout << tmp1 << std::endl;
    std::string tmp2(prec->name);
    std::cout << tmp2 << std::endl;
    //prec->val = "";
    return 0;
}

//Naming: devXxYyyy

static DevSupReg devStrOutCtrl = {
    6,
    NULL,
    NULL,
    (DEVSUPFUN)&initStrOutCtrl,
    NULL,
    (DEVSUPFUN)&ioStrOutCtrl,
    NULL};

#include <epicsExport.h>
extern "C"
{
    epicsExportAddress(dset, devStrOutCtrl);
}
