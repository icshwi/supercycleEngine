#ifndef SEQ_HPP_
#define SEQ_HPP_

#include <map>
#include <string>
#include "cmnbase.hpp"

#include <epicsTypes.h>

class SequenceHandler
{
private:
    std::map<std::string, epicsUInt32> evtcoderef;
    std::map<epicsUInt32, epicsUInt32> evt_tst_seq;
    std::map<epicsUInt32, epicsUInt32> tst_evt_seq;

public:
    SequenceHandler(std::map<std::string, epicsUInt32> evtrm);
    SequenceHandler(){};
    ~SequenceHandler();
    void init(std::map<std::string, epicsUInt32> evtrm);
    void write(std::map<std::string, std::string> &rowm);
    std::map<epicsUInt32, epicsUInt32> getSeq() { return tst_evt_seq; };
    std::vector<epicsUInt32> getSeqTst() { return cmn::map2vec<epicsUInt32>(tst_evt_seq, 0); };
    std::vector<epicsUInt32> getSeqEvt() { return cmn::map2vec<epicsUInt32>(tst_evt_seq, 1); };
};

#endif // SEQUENCE_HPP
