/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "seq.hpp"
#include "cmnbase.hpp"
#include "dlog.hpp"
#include "scenv.hpp"

namespace sce
{

SequenceHandler::SequenceHandler(const std::map<std::string, epicsUInt32>& evtrm)
{
  init(evtrm);
}

SequenceHandler::~SequenceHandler()
{
  DLOG(dlog::DEBUG2, << "")
}

void SequenceHandler::init(const std::map<std::string, epicsUInt32>& evtrm)
{
  DLOG(dlog::DEBUG2, << "")
  _evtcoderef = evtrm;
}

void SequenceHandler::write(const std::map<std::string, std::string>& rowm) const
{
  std::map<epicsUInt32, epicsUInt32> evt_tst_seq_ = {};

  for (auto const& it : _evtcoderef)
  {
    if (rowm.find(it.first) != rowm.end())
    {
      if (!rowm.at(it.first).empty())
        evt_tst_seq_[it.second] = (epicsUInt32)std::stol(rowm.at(it.first));
    }
  }

  // Sort the timestamps
  _tst_evt_seq = cmn::flip_map<epicsUInt32, epicsUInt32>(evt_tst_seq_);

  if (_tst_evt_seq.empty() == false)
  {
    // Terminate the sequence
    _tst_evt_seq[_tst_evt_seq.rbegin()->first + 1] = env::SeqEnd;
  }

  DLOG(dlog::DEBUG1, << " rowm " << rowm << " _tst_evt_seq " << _tst_evt_seq)
}

} // namespace sce
