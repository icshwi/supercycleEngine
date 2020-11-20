#include <stringoutRecord.h>
#include <stringinRecord.h>

//#include "devObj.h"

#include "devext.h"
#include <iostream>
#include <dbAccessDefs.h>

template <typename P>
static long add_record_property(dbCommon *prec, DBLINK *lnk)
{
  std::cout << "static long add_record_property(dbCommon *prec, DBLINK *lnk)" << std::endl;

  //std::string tmp_str(lnk->value.instio.string);
  //std::string tmp_str(prec->name);
  //std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << tmp_str << std::endl;
  //if (lnk->type != INST_IO)
  //  return S_db_errArg;

  return 0;
}

// template <typename REC, typename T>
// static inline long add_record_inp1(dbCommon *pcom)
// {
//   std::cout << "static inline long add_record_inp(dbCommon *pcom)" << std::endl;
//   REC *prec = (REC *)pcom;
//   return add_record_property<T>(pcom, &prec->inp);
// }

template <typename REC, typename T>
static inline long add_record_inp(dbCommon *pcom)
{
  std::cout << "static inline long add_record_inp(dbCommon *pcom)" << std::endl;
  REC *prec = (REC *)pcom; //desc

  std::cout << std::endl
            << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
  std::string tmp_str(prec->name);
  std::cout << std::endl
            << "...............................      " << tmp_str << std::endl;
  //return add_record_property<T>(pcom, &prec->inp);
  return 0;
}

// template <typename REC, typename T>
// static inline long add_record_out(dbCommon *pcom)
// {
//   std::cout << "static inline long add_record_out(dbCommon *pcom)" << std::endl;
//   REC *prec = (REC *)pcom;
//   return add_record_property<T>(pcom, &prec->out);
// }

static inline long init_record_empty(void *)
{
  std::cout << "static inline long init_record_empty(void *)" << std::endl;
  return 0;
}

// static inline long del_record_property(dbCommon *prec)
// {
//   std::cout << "static inline long del_record_property(dbCommon *prec)" << std::endl;
//   return 0;
// }

static inline long get_ioint_info_property(int, dbCommon *prec, IOSCANPVT *io)
{
  std::cout << "static inline long get_ioint_info_property(int, dbCommon *prec, IOSCANPVT *io)" << std::endl;
  return 0;
}

/************** stringin *************/

static long read_string(stringinRecord *prec)
{
  std::cout << "static long read_string(stringinRecord *prec)" << std::endl;
  return 0;
}

//static dsxt dxtStrInFromStr = {(&add_record_inp<stringinRecord, std::string>), &del_record_property};

// static DevSupReg devStrInFromStr = {
//     6,
//     NULL,
//     (DEVSUPFUN)&dxtStrInFromStr,
//     (DEVSUPFUN)&init_record_empty,
//     (DEVSUPFUN)&get_ioint_info_property,
//     (DEVSUPFUN)&read_string,
//     NULL};

static DevSupReg devStrInFromStr = {
    6,
    NULL,
    (DEVSUPFUN)&add_record_inp<stringinRecord, std::string>,
    (DEVSUPFUN)&init_record_empty,
    (DEVSUPFUN)&get_ioint_info_property,
    (DEVSUPFUN)&read_string,
    NULL};

// OBJECT_DSET(SIFromString,
//             (&add_record_inp<stringinRecord, std::string>),
//             &del_record_property,
//             &init_record_empty,
//             &read_string,
//             NULL);

/************ stringout *********/

// static long write_string(stringoutRecord *prec)
// {
//   return 0;
// }

// dsxt dxtSOFromString = {(&add_record_out<stringoutRecord, std::string>), &del_record_property};

// static DevSupReg devSOFromString = {
//     6,
//     NULL,
//     (DEVSUPFUN)&dxtSOFromString,
//     (DEVSUPFUN)&init_record_empty,
//     (DEVSUPFUN)&get_ioint_info_property,
//     (DEVSUPFUN)&write_string,
//     NULL};

// OBJECT_DSET(SOFromString,
//             (&add_record_out<stringoutRecord, std::string>),
//             &del_record_property,
//             &init_record_empty,
//             &write_string,
//             NULL);

#include <epicsExport.h>
extern "C"
{
  //epicsExportAddress(dset, devSOFromString);
  epicsExportAddress(dset, devStrInFromStr);
  //OBJECT_DSET_EXPORT(SIFromString);
  //OBJECT_DSET_EXPORT(SOFromString);
}
