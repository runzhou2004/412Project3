#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include "Server.h"
#include "RequestQueue.h"
#include "IPBlocker.h"

using namespace std;

class LoadBalancer {
    private:
        vector<Server*> servers;
        RequestQueue queue;
        IPBlocker blocker;
        int restCycles;
        int restCounter;
    
    public:
        LoadBalancer(int initialServers, int rest);
        ~LoadBalancer();

        void generateReq(Request* r);
        void processServers();
        void scaleServers();
        int getServerCount();
        int getQueueSize();
};

#endif