#include "dlog.hpp"

namespace io
{

LOGCONFIG &RegistrarLOGCFG()
{
    static LOGCONFIG LOGCFG;
    return LOGCFG;
}

} // namespace io
