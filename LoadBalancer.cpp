#include "LoadBalancer.h"
#include <iostream>

using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

LoadBalancer::LoadBalancer(int initialServers, int rest, std::ofstream& log) : logFile(log), currentCycle(0), restCycles(rest), restCounter(0) {
    for (int i = 0; i < initialServers; i++) servers.push_back(new Server(i));
}

LoadBalancer::~LoadBalancer() {
    while (!queue.empty()) delete queue.dequeue();
    for (auto s:servers) delete s;
}

void LoadBalancer::generateReq(Request* r) {
    if (!blocker.isBlocked(r->ipIn)) {
        queue.enqueue(r);
        totalGenerated++;
    }
    else {
        totalBlocked++;
        logFile << "[CYCLE " << currentCycle << "] Blocked Request from IP: " << r->ipIn << endl;
        delete r;
    }
}

void LoadBalancer::processCycle() {
    currentCycle++;
    for (auto s:servers) {
        s->processCycle();
        if (s->isDone()) {
            totalRequestsProcessed++;
            s->clear();
        }
    }
    for (auto s:servers) {
        if (s->isIdle() && !queue.empty()) s->assign(queue.dequeue());
    }
    scaleServers();
    if (queue.size() > maxQueueSize) maxQueueSize = queue.size();
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
        serversAdded++;
        cout << GREEN "[CYCLE " << currentCycle << "] Added Server! Total Servers: " << servers.size() << RESET << endl;
        logFile << "------------------------------" << endl;
        logFile << "[CYCLE " << currentCycle << "] Added Server! Total Servers: " << servers.size() << endl;
        restCounter = restCycles;
    }
    else if (qSize < 50*sCount && sCount > 1) {
        if (!servers.back()->isIdle()) return;
        delete servers.back();
        servers.pop_back();
        serversRemoved++;
        cout << RED "[CYCLE " << currentCycle << "] Removed Server! Total Servers: " << servers.size() << RESET << endl;
        logFile << "------------------------------" << endl;
        logFile << "[CYCLE " << currentCycle << "] Removed Server! Total Servers: " << servers.size() << endl;
    }
}

int LoadBalancer::getServerCount() {
    return servers.size();
}

int LoadBalancer::getQueueSize() {
    return queue.size();
}

int LoadBalancer::getGeneratedRequests() {
    return totalGenerated;
}

int LoadBalancer::getProcessedRequests() {
    return totalRequestsProcessed;
}

int LoadBalancer::getBlockedRequests() {
    return totalBlocked;
}

int LoadBalancer::getServersAdded() {
    return serversAdded;
}

int LoadBalancer::getServersRemoved() {
    return serversRemoved;
}

int LoadBalancer::getMaxQueueSize() {
    return maxQueueSize;
}