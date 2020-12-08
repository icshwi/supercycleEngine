/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "ioblock.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

#include <iostream>

namespace io
{

  int IOBlock::init(std::map<std::string, std::string> argm)
  {
    if (cmn::file::exists(argm[GETVARNAME(databufferLink)]))
      databufferLink = argm[GETVARNAME(databufferLink)];

    if (cmn::file::exists(argm[GETVARNAME(mevtsLink)]))
      mevtsLink = argm[GETVARNAME(mevtsLink)];

    if (cmn::file::exists(argm[GETVARNAME(sctableRoot)]))
      sctableRoot = argm[GETVARNAME(sctableRoot)];

    dlog::Print(dlog::INFO) << __COMPACT_PRETTY_FUNCTION__ << " databufferLink " << databufferLink;
    dlog::Print(dlog::INFO) << __COMPACT_PRETTY_FUNCTION__ << " mevtsLink " << mevtsLink;
    dlog::Print(dlog::INFO) << __COMPACT_PRETTY_FUNCTION__ << " sceconfigLink " << sceconfigLink;
    dlog::Print(dlog::INFO) << __COMPACT_PRETTY_FUNCTION__ << " getSCTableLink() " << getSCTableLink();

    DBuf_yml.init(databufferLink);
    SCEConfig_yml.init(sceconfigLink);
    mEvts_yml.init(mevtsLink);
    _CSVStrMap.init(getSCTableLink());

    Seq.init(mEvts_yml.getMap());

    return 0;
  }

  int IOBlock::dbSync(std::map<std::string, std::string> &argms)
  {

    for (auto const &it : argms)
    {
      if (it.first.find(GETVARNAME(SCTable)))
        SCTable = it.second;
      if (it.first.find(GETVARNAME(PBState)))
        PBState = it.second;
      if (it.first.find(GETVARNAME(PBMod)))
        PBMod = it.second;
      if (it.first.find(GETVARNAME(PBDest)))
        PBDest = it.second;
    }

    return 0;
  }

  IOBlock &RegisteredIOBlock()
  {
    static IOBlock io_block;
    return io_block;
  }

} // namespace io
