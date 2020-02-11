
// System
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <map>

// Epics
#include "cadef.h"

// Base
#include "dlog.hpp"
#include "cmnbase.hpp"

// Cycle
#include "cacback.hpp"
#include "engine.hpp"
// Cycle System - Threading
#include <thread>             // std::thread

// Run the engine
#include "ioblock.hpp"

// Log config container
io::structlog io::LOGCFG(true,io::DEBUG);

int main(int argc,char **argv)  //for the future
//int main()
{
    io::IOBlock io_block(argc, argv);
    cmn::gcc_assert();

    // Define the sychronization
    clb::CaCallbackManager cacback;
    cacback.create(io_block.get_PSCE()+"EvtData", engineCbSpark);

    // Engine Start
    std::thread engine_cycle_wait;
    while(true)
    {
        // Init the engine
        engine_cycle_wait = std::thread(engineCycleWait);
        // Wait for the engine cycle
        engine_cycle_wait.join();
        // Move the engine
        engineCycle(io_block);
        // Test the synchronization
        io::LOG(io::DEBUG) << "main() engine_cycle_wait.join() cmn::wclock_s() " << cmn::wclock_s();
    }

    io::LOG(io::ERROR) << "main() supercycleEngine finished!";
    return 0;
}

/*
int main()
{
    io::JsonEVT evts("../reftabs/init/mevts-ess.json");
    std::cout << evts.getEvtCode("DATAS") << std::endl;
}
*/
