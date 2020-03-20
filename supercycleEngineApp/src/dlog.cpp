/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "dlog.hpp"

namespace io
{

LOGCONFIG &RegisteredLOGCFG()
{
    static LOGCONFIG LOGCFG;
    return LOGCFG;
}

} // namespace io
