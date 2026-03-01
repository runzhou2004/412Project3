#ifndef SWITCH_H
#define SWITCH_H

#include "LoadBalancer.h"
#include "Request.h"

/**
 * @class Switch
 * @brief The Switch class is responsible for routing incoming requests to the appropriate LoadBalancer based on the type of job specified in the Request object. It maintains pointers to both the processing and streaming LoadBalancers and provides a method to route requests accordingly.
 * The Switch class serves as a central component in the load balancing system, directing traffic to the correct LoadBalancer based on the job type (e.g., 'P' for processing or 'S' for streaming). This allows for efficient handling of different types of requests and helps to optimize the performance of the overall system.
 */
class Switch {
    private:
        LoadBalancer* processingLB;
        LoadBalancer* streamingLB;

    public:
        /**
         * @param p A pointer to the LoadBalancer responsible for processing requests (job type 'P').
         * @param s A pointer to the LoadBalancer responsible for streaming requests (job type 'S').
         * The constructor initializes the Switch with pointers to the processing and streaming LoadBalancers, allowing it to route requests to the appropriate LoadBalancer based on the job type specified in the Request objects
         */
        Switch(LoadBalancer* p, LoadBalancer* s);

        /**
         * @param r A pointer to the Request object to be routed. The caller is responsible for managing the memory of the Request object, as it will be processed and deleted by the LoadBalancer.
         * This method checks the job type of the incoming Request and routes it to the appropriate LoadBalancer. 
         * If the job type is 'P', it calls the generateReq method of the processing LoadBalancer; 
         * if the job type is 'S', it calls the generateReq method of the streaming LoadBalancer. 
         * If the job type is not recognized, it deletes the Request object to free up memory and prevent memory leaks, 
         * as the request cannot be processed by either LoadBalancer. This method ensures that requests are directed 
         * to the correct LoadBalancer based on their job type, 
         * allowing for efficient handling of different types of requests in the system.
         */
        void routeRequest(Request* r);
};

#endif