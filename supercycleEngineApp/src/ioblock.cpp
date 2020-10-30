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

  IOBlock::~IOBlock()
  {
    io::LOG(io::DEBUG) << "IOBlock::~IOBlock()";
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

    DBuf_yml.init(databufferLink);
    inhibitEvts_yml.init(sceconfigLink);
    mEvts_yml.init(mevtsLink);

    sctable.init(getSCTableLink());
    Seq.init(mEvts_yml.getMap());

    io::LOG(io::INFO) << "IOBlock::init() databufferLink " << databufferLink;
    io::LOG(io::INFO) << "IOBlock::init() mevtsLink " << mevtsLink;
    io::LOG(io::INFO) << "IOBlock::init() sceconfigLink " << sceconfigLink;
    io::LOG(io::INFO) << "IOBlock::init() getSCTableLink() " << getSCTableLink();

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
