/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "iobase.hpp"
#include "cmnbase.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace io
{

  std::string db_inp_val(std::string args, std::string key)
  {
    std::vector<std::string> argvs = cmn::str::split(args);

    for (auto &is : argvs)
    {
      size_t pos = is.find(key + '=');
      if (pos != std::string::npos)
      {
        pos = pos + key.length();
        return is.substr(pos + 1);
      }
    }
    return {};
  }

} // namespace io
