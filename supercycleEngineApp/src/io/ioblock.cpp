/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "ioblock.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"
#include "csvvec.hpp"

#include <iostream>

namespace io
{

  IOBlock::~IOBlock()
  {
    dlog::Print(dlog::DEBUG) << "IOBlock::~IOBlock()";
    // Kill all not used processes
    // SEVCHK(ca_task_exit(), "ERROR ca_task_exit failure");
  }

  int IOBlock::init(std::map<std::string, std::string> argm)
  {
    if (cmn::isFile(argm[GETVARNAME(databufferLink)]))
      databufferLink = argm[GETVARNAME(databufferLink)];

    if (cmn::isFile(argm[GETVARNAME(mevtsLink)]))
      mevtsLink = argm[GETVARNAME(mevtsLink)];

    if (cmn::isFile(argm[GETVARNAME(sctableRoot)]))
      sctableRoot = argm[GETVARNAME(sctableRoot)];

    dlog::Print(dlog::INFO) << "IOBlock::init() databufferLink " << databufferLink;
    dlog::Print(dlog::INFO) << "IOBlock::init() mevtsLink " << mevtsLink;
    dlog::Print(dlog::INFO) << "IOBlock::init() sceconfigLink " << sceconfigLink;
    dlog::Print(dlog::INFO) << "IOBlock::init() getSCTableLink() " << getSCTableLink();

    DBuf_yml.init(databufferLink);
    SCEConfig_yml.init(sceconfigLink);
    mEvts_yml.init(mevtsLink);

    io::CSVStrMap::instance().init(getSCTableLink());

    Seq.init(mEvts_yml.getMap());

    return 0;
  }

  int IOBlock::dbSync(std::map<std::string, std::string> &argms)
  {

    for (auto const &it : argms)
    {
      if (cmn::isSubstring(it.first, GETVARNAME(SCTable)))
        SCTable = it.second;
      if (cmn::isSubstring(it.first, GETVARNAME(PBState)))
        PBState = it.second;
      if (cmn::isSubstring(it.first, GETVARNAME(PBMod)))
        PBMod = it.second;
      if (cmn::isSubstring(it.first, GETVARNAME(PBDest)))
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
