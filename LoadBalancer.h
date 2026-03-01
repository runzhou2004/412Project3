#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include "Server.h"
#include "RequestQueue.h"
#include "IPBlocker.h"

using namespace std;

/**
 * @bclass LoadBalancer
 * @brief The LoadBalancer class manages a pool of servers, a queue of incoming requests, and an IP blocker to handle traffic.
 * It can generate requests, process them through the servers, and dynamically scale the number of servers
 * based on the current load (queue size).
 * The LoadBalancer also implements a cooldown mechanism to prevent rapid scaling of servers.
 * It provides methods to get the current number of servers and the size of the request queue for monitoring purposes.
 * The LoadBalancer is designed to efficiently distribute incoming requests while maintaining performance and resource utilization.
 * @note The LoadBalancer class is a central component of the system, responsible for managing the flow of requests and ensuring that they are processed in a timely manner while also handling scaling and blocking of IP addresses as needed.
 */
class LoadBalancer {
    private:
        vector<Server*> servers;
        RequestQueue queue;
        IPBlocker blocker;
        int restCycles;
        int restCounter;
    
    public:
        /**
         * @brief Constructs a LoadBalancer with a specified number of initial servers and a cooldown period for scaling.
         * @param initialServers The number of servers to start with.
         */
        LoadBalancer(int initialServers, int rest);
        /**
         * @brief Destructor for the LoadBalancer class, responsible for cleaning up dynamically allocated Server objects.
         */
        ~LoadBalancer();

        /**
         * @brief Generates a new request and adds it to the queue if the source IP is not blocked. If the IP is blocked, the request is discarded.
         * @param r A pointer to the Request object to be generated.
         */
        void generateReq(Request* r);
        /**
         * @brief Processes the requests on each server for a single cycle. This includes checking if any servers have completed their current request and clearing them, as well as assigning new requests from the queue to any idle servers.
         */
        void processServers();
        /**
         * @brief Processes a single cycle of the load balancer, which includes processing requests on each server, assigning new requests from the queue to idle servers, and scaling the number of servers based on the current load.
         */
        void processCycle();
        /**
         * @brief Scales the number of servers based on the current load (queue size) and the number of active servers. If the queue size exceeds a certain threshold, a new server is added. If the queue size is below a certain threshold and there are more than one server, a server is removed. The method also implements a cooldown mechanism to prevent rapid scaling.
         */
        void scaleServers();
        /**
         * @brief Returns the current number of servers in the load balancer.
         * @return The number of servers.
         */
        int getServerCount();
        /**
         * @brief Returns the current size of the request queue.
         * @return The number of requests in the queue.
         */
        int getQueueSize();

        int getGeneratedRequests();
        int getProcessedRequests();
        int getServersAdded();
        int getServersRemoved();
        int getMaxQueueSize();
};

#endif