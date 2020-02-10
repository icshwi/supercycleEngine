
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "scenv.hpp"
#include "ioblock.hpp"

void engineCbSpark(struct event_handler_args eha);
void engineCycleWait();
int engineCycle(io::IOBlock &);

#endif // ENGINE_HPP
