
#ifndef CACBACK_HPP
#define CACBACK_HPP

#include <string>
#include "cadef.h"


namespace clb
{

struct PVNODE{
    char value[20];
    chid ch_id;
    evid ev_id;
};

void eventCallbackTest(struct event_handler_args eha);

class CaCallbackManager {
    public:
        void create(std::string pvname, caEventCallBackFunc *pFunc=eventCallbackTest);
    private:
        struct PVNODE pv;
};

} //namespace

#endif // CACBACK_HPP
