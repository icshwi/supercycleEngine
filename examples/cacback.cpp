#include "cacback.hpp"
#include "dlog.hpp"

//#include <stddef.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>

//#include "dbDefs.h"
//#include "epicsString.h"
//#include "cantProceed.h"

namespace clb
{

static void printChidInfo(chid chid, char const *message)
{
    io::LOG(io::INFO) << "printChidInfo " << message << " pv " << ca_name(chid) << " type " << ca_field_type(chid) \
        << " nelements " << ca_element_count(chid) << " host " << ca_host_name(chid) \
        << " read " << ca_read_access(chid) << " write " << ca_write_access(chid) << " state " << ca_state(chid);
}

static void exceptionCallback(struct exception_handler_args args)
{
    io::LOG(io::DEBUG2) << "exceptionCallback";

    chid chid = args.chid;
    long stat = args.stat; /* Channel access status code*/
    const char  *channel;
    static char noname[] = "unknown";

    channel = (chid ? ca_name(chid) : noname);

    if(chid) printChidInfo(chid,"exceptionCallback");
    // printf("exceptionCallback stat %s channel %s\n", ca_message(stat),channel);
    io::LOG(io::DEBUG) << "exceptionCallback stat " <<  ca_message(stat) << " channel " << channel;
}

static void connectionCallback(struct connection_handler_args args)
{
    io::LOG(io::DEBUG) << "connectionCallback";

    chid chid = args.chid;
    printChidInfo(chid,"connectionCallback");
}

static void accessRightsCallback(struct access_rights_handler_args args)
{
    io::LOG(io::DEBUG) << "accessRightsCallback";

    chid chid = args.chid;
    printChidInfo(chid,"accessRightsCallback");
}

void eventCallbackTest(struct event_handler_args eha)
{
    io::LOG(io::DEBUG) << "eventCallbackTest";

    chid chid = eha.chid;

    if(eha.status!=ECA_NORMAL) {
        printChidInfo(chid,"eventCallbackTest");
    }
    else {
        char *pdata = (char *)eha.dbr;
        printf("Event Callback: %s = %s\n",ca_name(eha.chid),pdata);
    }
    //ca_detach_context();  //not necessary
}

void CaCallbackManager::create(std::string pvname, caEventCallBackFunc *pFunc)
{
    io::LOG(io::DEBUG) << "CaCallbackManager::create";

    SEVCHK(ca_context_create(ca_enable_preemptive_callback),"ca_context_create");
    SEVCHK(ca_add_exception_event(exceptionCallback,NULL),"ca_add_exception_event");
    SEVCHK(ca_create_channel(pvname.c_str(),connectionCallback,&pv,20,&pv.ch_id),"ca_create_channel");
    SEVCHK(ca_replace_access_rights_event(pv.ch_id,accessRightsCallback),"ca_replace_access_rights_event");
    SEVCHK(ca_create_subscription(DBR_STRING,1,pv.ch_id,DBE_VALUE,pFunc,&pv,&pv.ev_id),"ca_create_subscription");

    io::LOG(io::DEBUG) << "CaCallbackManager::create finished";
}


} //namespace
