#ifndef SEQ_HPP_
#define SEQ_HPP_

#include <map>
#include <string>

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
};

#endif // SEQUENCE_HPP