#ifndef SEQ_HPP_
#define SEQ_HPP_

#include <map>
#include <string>
#include "cmnbase.hpp"

class SequenceHandler
{
private:
    std::map<std::string, uint32_t> evtcoderef;
    std::map<uint32_t, uint32_t> evt_tst_seq;
    std::map<uint32_t, uint32_t> tst_evt_seq;

public:
    SequenceHandler(std::string evgs, std::map<std::string, uint32_t> evtrm);
    SequenceHandler(){};
    ~SequenceHandler();
    void init(std::string evgs, std::map<std::string, uint32_t> evtrm);
    void write(std::map<std::string, std::string> &rowm);
    std::map<uint32_t, uint32_t> getSeq() { return tst_evt_seq; };
    std::vector<uint32_t> getSeqTst() { return cmn::map2vec<uint32_t>(tst_evt_seq, 0); };
    std::vector<uint32_t> getSeqEvt() { return cmn::map2vec<uint32_t>(tst_evt_seq, 1); };
};

#endif // SEQUENCE_HPP
