/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "seq.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"
#include "scenv.hpp"

namespace sce
{

  SequenceHandler::SequenceHandler(std::map<std::string, epicsUInt32> evtrm)
  {
    dlog::Print(dlog::DEBUG2) << "SequenceHandler::SequenceHandler()";
    init(evtrm);
  }

  SequenceHandler::~SequenceHandler()
  {
    dlog::Print(dlog::DEBUG2) << "SequenceHandler::~SequenceHandler()";
  }

  void SequenceHandler::init(std::map<std::string, epicsUInt32> evtrm)
  {
    dlog::Print(dlog::DEBUG2) << "SequenceHandler::init()";
    evtcoderef = evtrm;
  }

  void SequenceHandler::write(std::map<std::string, std::string> &rowm)
  {
    dlog::Print(dlog::DEBUG2) << "SequenceHandler::write()";
    evt_tst_seq = {};

    for (auto const &it : evtcoderef)
    {
      if (rowm[it.first].empty() == false)
      {
        evt_tst_seq[it.second] = std::stol(rowm[it.first]);
      }
    }

    // Sort the timestamps
    tst_evt_seq = cmn::flip_map<epicsUInt32, epicsUInt32>(evt_tst_seq);

    if (tst_evt_seq.empty() == false)
    {
      // Terminate the sequence
      tst_evt_seq[tst_evt_seq.rbegin()->first + 1] = env::SeqEnd;
    }

    dlog::Print(dlog::DEBUG1) << "SequenceHandler::write() rowm " << rowm << " tst_evt_seq " << tst_evt_seq;
  }

} // namespace sce
