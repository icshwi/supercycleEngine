/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#pragma once

#include "cmnbase.hpp"
#include <map>
#include <string>

#include <epicsTypes.h>

namespace sce
{
class SequenceHandler
{
private:
  std::map<std::string, epicsUInt32> _evtcoderef;
  mutable std::map<epicsUInt32, epicsUInt32> _tst_evt_seq;

public:
  SequenceHandler(){};
  explicit SequenceHandler(const std::map<std::string, epicsUInt32>& evtrm);
  ~SequenceHandler();
  void init(const std::map<std::string, epicsUInt32>& evtrm);
  void write(const std::map<std::string, std::string>& rowm) const;
  std::map<epicsUInt32, epicsUInt32> getSeqMap() const { return _tst_evt_seq; };
  std::vector<epicsUInt32> getSeqTst() const { return cmn::map1d2vec<epicsUInt32>(_tst_evt_seq, 0); };
  std::vector<epicsUInt32> getSeqEvt() const { return cmn::map1d2vec<epicsUInt32>(_tst_evt_seq, 1); };
  std::vector<epicsUInt32> getSeqVec() const { return cmn::map2d2vec<epicsUInt32>(_tst_evt_seq); };
};

} // namespace sce
