#ifndef SWITCH_H
#define SWITCH_H

#include "LoadBalancer.h"
#include "Request.h"

/**
 * @class Switch

*/
class Switch {
    private:
        LoadBalancer* processingLB;
        LoadBalancer* streamingLB;

    public:
        Switch(LoadBalancer* p, LoadBalancer* s);
        void routeRequest(Request* r);
};

#endif