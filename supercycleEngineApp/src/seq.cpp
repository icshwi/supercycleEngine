#include "seq.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"
#include "scenv.hpp"

SequenceHandler::SequenceHandler(std::string evgs, std::map<std::string, epicsUInt32> evtrm)
{
    io::LOG(io::DEBUG2) << "SequenceHandler::SequenceHandler() evgs " << evgs;
    init(evgs, evtrm);
}

SequenceHandler::~SequenceHandler()
{
    io::LOG(io::DEBUG2) << "SequenceHandler::~SequenceHandler()";
}

void SequenceHandler::init(std::string evgs, std::map<std::string, epicsUInt32> evtrm)
{
    io::LOG(io::DEBUG2) << "SequenceHandler::init() evgs " << evgs;
    evtcoderef = evtrm;
}

void SequenceHandler::write(std::map<std::string, std::string> &rowm, epicsUInt32 offset)
{
    io::LOG(io::DEBUG2) << "SequenceHandler::write()";
    evt_tst_seq = {};

    evt_tst_seq[env::DATA] = offset;

    for (auto const &it : evtcoderef)
    {
        if (rowm[it.first].empty() == false)
        {
            evt_tst_seq[it.second] = std::stol(rowm[it.first]);
        }
    }

    // Sort the timestamps
    tst_evt_seq = cmn::flip_map<epicsUInt32, epicsUInt32>(evt_tst_seq);

    // Terminate the sequence
    tst_evt_seq[tst_evt_seq.rbegin()->first + 1] = env::SEQ_END;

    io::LOG(io::DEBUG1) << "SequenceHandler::write() rowm " << cmn::map2str<std::string, std::string>(rowm);
    io::LOG(io::DEBUG1) << "SequenceHandler::write() tst_evt_seq " << cmn::map2str<epicsUInt32, epicsUInt32>(tst_evt_seq);
}
