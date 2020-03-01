
#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "scenv.hpp"
#include "ioblock.hpp"

#include <epicsTypes.h>

int engineCycle(io::IOBlock &);
int sctableSwitch(io::IOBlock &io);

#endif // ENGINE_HPP
