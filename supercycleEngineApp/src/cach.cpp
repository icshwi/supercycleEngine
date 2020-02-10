
#include "cach.hpp"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cadef.h"

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <stdexcept>
#include "dlog.hpp"

CACh::CACh(std::string pvstr)
{
    io::LOG(io::DEBUG2) << "CACh::CACh pvstr";
    init(pvstr);
}

CACh::CACh()
{
    io::LOG(io::DEBUG2) << "CACh::CACh Empty Constructor";
}

CACh::~CACh()
{
    io::LOG(io::DEBUG2) << "CACh::~CACh()";
    close();
}

void
CACh::close()
{
    io::LOG(io::DEBUG2) << "CACh::close()";
    SEVCHK(ca_clear_channel(id),(msgerr + name + " ca_clear_channel").c_str());
    //Close all channels
    //SEVCHK(ca_task_exit(), "ERROR ca_task_exit failure");
}

void
CACh::init(std::string pvstr)
{
    io::LOG(io::DEBUG2) << "CACh::init()";
    name = pvstr;
    SEVCHK(ca_context_create(ca_enable_preemptive_callback),(msgerr + name + " ca_context_create").c_str());
    SEVCHK(ca_create_channel(pvstr.c_str(),NULL,NULL,10,&id),(msgerr + name + " ca_create_channel").c_str());
    SEVCHK(ca_pend_io(0.5),(msgerr + name + " ca_pend_io " + "CACh::init").c_str());
}

void
CACh::caGet(int type, int val_size, void *val)
{
    io::LOG(io::DEBUG2) << "CACh::caGet() type " << type << " val_size " << val_size << " val " << val;
    SEVCHK(ca_array_get(type,val_size,id,(void *)val),(msgerr + name + " ca_array_get").c_str());
    SEVCHK(ca_pend_io(0.5),(msgerr + name + " ca_pend_io " + "CACh::caGet").c_str());
}

void
CACh::caPut(int type, int val_size, void *val)
{
    io::LOG(io::DEBUG2) << "CACh::caPut() type " << type << " val_size " << val_size << " val " << val;
    SEVCHK(ca_array_put(type,val_size,id,(void *)val),(msgerr + name + " ca_array_put").c_str());
    SEVCHK(ca_pend_io(0.5),(msgerr + name + " ca_pend_io " + "CACh::caPut").c_str());
}

int
CACh::get(int &arg)
{
    caGet(DBR_LONG, 1u, &arg);
    return arg;
}

uint
CACh::get(uint &arg)
{
    caGet(DBR_LONG, 1u, &arg);
    return arg;
}

void
CACh::get(std::string &args)
{
    char tmps[200];
    caGet(DBR_STRING, 1u, &tmps);
    args = tmps;
}

void
CACh::put(uint arg)
{
    caPut(DBR_LONG, 1u, &arg);
}

void
CACh::put(int arg)
{
    caPut(DBR_LONG, 1u, &arg);
}

void
CACh::put(std::string &args)
{
    caPut(DBR_STRING, 1u, &args);
}

void
CACh::put_vec(std::vector<uint> val_vec)
{
    caPut(DBR_LONG, val_vec.size(), &val_vec[0]);
}

void
CACh::put_vec(std::vector<int> val_vec)
{
    caPut(DBR_LONG, val_vec.size(), &val_vec[0]);
}

/*
void careg_test(std::string pvstr)
{
    SEVCHK(ca_context_create(ca_disable_preemptive_callback),"ERROR ca_context_create");
    SEVCHK(ca_create_channel(pvstr.c_str(),NULL,NULL,10,&ch_id),"ERROR ca_create_channel failure");
    SEVCHK(ca_pend_io(0.5),"ERROR ca_pend_io failure");

    SEVCHK(ca_array_get(DBR_LONG,1u,ch_id,(void *)&arg_tmp),"ERROR ca_array_get failure");
    SEVCHK(ca_pend_io(0.5),"ERROR ca_pend_io failure");
    //SEVCHK(ca_clear_channel(ch_id),"ERROR ca_clear_channel failure");

    std::cout << "CAReg::get() arg_tmp " << arg_tmp <<std::endl;
}

void careg_test1(std::string pvstr)
{
    chid mychid;
    int arg;

    SEVCHK(ca_context_create(ca_disable_preemptive_callback),"ERROR ca_context_create");
    //SEVCHK(ca_context_create(ca_enable_preemptive_callback),"ca_context_create");

    SEVCHK(ca_create_channel(pvstr.c_str(),NULL,NULL,10,&mychid),"ERROR ca_create_channel failure");
    SEVCHK(ca_pend_io(0.5),"ERROR ca_pend_io failure");

    SEVCHK(ca_array_get(DBR_LONG,1u,mychid,(void *)&arg),"ERROR ca_array_get failure");

    SEVCHK(ca_pend_io(0.5),"ERROR ca_pend_io failure");
    SEVCHK(ca_clear_channel(mychid),"ERROR ca_clear_channel failure");

    std::cout << "CAReg::get() arg " << arg <<std::endl;
}
*/
