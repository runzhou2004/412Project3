#include "LoadBalancer.h"
#include <iostream>

LoadBalancer::LoadBalancer(int initialServers, int rest) : restCycles(rest), restCounter(0) {
    for (int i = 0; i < initialServers; i++) servers.push_back(new Server(i));
}

LoadBalancer::~LoadBalancer() {
    for (auto s:servers) delete s;
}

void LoadBalancer::generateReq(Request* r) {
    if (!blocker.isBlocked(r->ipIn)) queue.enqueue(r);
    else delete r;
}

void LoadBalancer::processCycle() {
    for (auto s:servers) {
        s->processCycle();
        if (s->isDone()) s->clear();
    }
    for (auto s:servers) {
        if (s->isIdle() && !queue.empty()) s->assign(queue.dequeue());
    }
    scaleServers();
}

void LoadBalancer::scaleServers() {
    if (restCounter > 0) {
        restCounter--;
        return;
    }

    int qSize = queue.size();
    int sCount = servers.size();

    if (qSize > 80*sCount) {
        servers.push_back(new Server(sCount));
        cout << "Added Server!";
        restCounter = restCycles;
    }
    else if (qSize < 50*sCount && sCount > 1) {
        delete servers.back();
        servers.pop_back();
        cout << "Removed Server!";
        restCounter = restCycles;
    }
}