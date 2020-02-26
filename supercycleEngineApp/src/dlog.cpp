#include "dlog.hpp"

namespace io
{

LOGCONFIG &RegisteredLOGCFG()
{
    static LOGCONFIG LOGCFG;
    return LOGCFG;
}

} // namespace io
