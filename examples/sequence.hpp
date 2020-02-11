#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <map>
#include <cach.hpp>
#include <string>

class SequenceHandler
{
private:
    std::map<std::string,uint32_t> evtcoderef;
    std::map<uint32_t,uint32_t> evt_tst_seq;
    int seqSel=0;
    void seq0_put();
    void seq1_put();
    void multiplexer_seqput();

protected:
    CACh Seq0EvtCodeCa, Seq0TimestampCa, Seq0CmtCa, Seq0EnCa;
    CACh Seq1EvtCodeCa, Seq1TimestampCa, Seq1CmtCa, Seq1EnCa;

public:
    SequenceHandler(std::string evgs, std::map<std::string,uint32_t> evtrm);
    SequenceHandler(){};
    ~SequenceHandler();
    void init(std::string evgs, std::map<std::string,uint32_t> evtrm);
    //void caPut(int ch, std::map<uint32_t,uint32_t> );
    void update(std::map<std::string,std::string> & rowm);
    void put();
    std::map<uint32_t,uint32_t> getEvtTstSeq(){return evt_tst_seq;};
};

//SoftSeq0-EvtCode-SP
//SoftSeq0-Timestamp-SP


#endif // SEQUENCE_HPP