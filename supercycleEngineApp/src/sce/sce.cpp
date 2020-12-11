/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-11-10
 */

#include "sce.hpp"
#include "ioblock.hpp"
#include "object.hpp"
#include "version.h"

std::string SCE::getSwVersion()
{
  return SCE_VERSION;
}

std::string SCE::getScTable()
{
  return io::RegisteredIOBlock().CSVTab.getFile();
}
