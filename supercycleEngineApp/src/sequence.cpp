#include "sequence.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"
#include "scenv.hpp"

SequenceHandler::SequenceHandler(std::string evgs, std::map<std::string,uint32_t> evtrm)
{
    io::LOG(io::DEBUG2) << "SequenceHandler::SequenceHandler() evgs " << evgs;
    init(evgs, evtrm);
}

SequenceHandler::~SequenceHandler()
{
    io::LOG(io::DEBUG2) << "SequenceHandler::~SequenceHandler()";
}

void
SequenceHandler::init(std::string evgs, std::map<std::string,uint32_t> evtrm)
{
    io::LOG(io::DEBUG2) << "SequenceHandler::init() evgs " << evgs;
    evtcoderef = evtrm;
    // Sequence0 memory map
    Seq0EvtCodeCa.init   (evgs+"SoftSeq0-EvtCode-SP");
    Seq0TimestampCa.init (evgs+"SoftSeq0-Timestamp-SP");
    // Sequence0 control
    Seq0EnCa.init        (evgs+"SoftSeq0-Enable-Cmd");
    Seq0CmtCa.init       (evgs+"SoftSeq0-Commit-Cmd");
    // Sequence1 memory map
    Seq1EvtCodeCa.init   (evgs+"SoftSeq1-EvtCode-SP");
    Seq1TimestampCa.init (evgs+"SoftSeq1-Timestamp-SP");
    // Sequence1 control
    Seq1EnCa.init        (evgs+"SoftSeq1-Enable-Cmd");
    Seq1CmtCa.init       (evgs+"SoftSeq1-Commit-Cmd");
}

void
SequenceHandler::update(std::map<std::string,std::string> & rowm)
{
    io::LOG(io::DEBUG2) << "SequenceHandler::update()";
    evt_tst_seq = {};
    for(auto const &it: evtcoderef)
    {
        if(rowm[it.first].empty() == false)
        {
            evt_tst_seq[it.second]=std::stol(rowm[it.first]);
        }
        //if( rowm[it] )
    }

    io::LOG(io::DEBUG1) << "SequenceHandler::update() rowm "        << cmn::map2str<std::string,std::string>(rowm);
    io::LOG(io::DEBUG1) << "SequenceHandler::update() evt_tst_seq " << cmn::map2str<uint,uint>(evt_tst_seq);
}


void
SequenceHandler::seq0_put()
{
    // Sort the timestamps
    std::map<uint32_t,uint32_t> tst_evt_seq_tmp = cmn::flip_map<uint32_t,uint32_t>(evt_tst_seq);

    Seq0EvtCodeCa.put_vec   (cmn::map2vec<uint32_t>(tst_evt_seq_tmp,1));
    Seq0TimestampCa.put_vec (cmn::map2vec<uint32_t>(tst_evt_seq_tmp,0));
    // Commit
    Seq0CmtCa.put(1);
}

void
SequenceHandler::seq1_put()
{
    // Sort the timestamps
    std::map<uint32_t,uint32_t> tst_evt_seq_tmp = cmn::flip_map<uint32_t,uint32_t>(evt_tst_seq);

    Seq1EvtCodeCa.put_vec   (cmn::map2vec<uint32_t>(tst_evt_seq_tmp,1));
    Seq1TimestampCa.put_vec (cmn::map2vec<uint32_t>(tst_evt_seq_tmp,0));
    // Commit
    Seq1CmtCa.put(1);
}

void
SequenceHandler::multiplexer_seqput()
{
    switch(seqSel)
    {
        case 0 :
            Seq1EnCa.put(0);    // Disable
            seq0_put();         // Commit
            Seq0EnCa.put(1);    // Enable
            seqSel = 1;         // Next cycle - other sequence
        break;
        case 1 :
            Seq0EnCa.put(0);    // Disable
            seq1_put();         // Commit
            Seq1EnCa.put(1);    // Enable
            seqSel = 0;         // Next cycle - other sequence
        break;
        default :
            io::LOG(io::ERROR) << "SequenceHandler::multiplexer_seqput() wrong argument of seqSel " << seqSel;
        break;
    }
}

void
SequenceHandler::put()
{
    evt_tst_seq[env::SEQ_END] = 50000;
    evt_tst_seq[env::DATA] = 30000;
    // Submit the sequence
    multiplexer_seqput();
}
