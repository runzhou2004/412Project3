#include "Switch.h"

using namespace std;

Switch::Switch(LoadBalancer* p, LoadBalancer* s) {
    processingLB = p;
    streamingLB = s;
}
void Switch::routeRequest(Request* r) {
    if (r->jobType == 'P') processingLB->generateReq(r);
    else if (r->jobType == 'S') streamingLB->generateReq(r);
}