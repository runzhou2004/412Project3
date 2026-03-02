/**
 * @file Server.h
 * @brief The Server class represents a server in the load balancing system, responsible for processing incoming requests. Each Server object maintains its own state, including whether it is currently busy, the request it is processing, and the time remaining to complete the request.
 * The Server class provides methods to assign a new request to the server, process a cycle of
 */

#ifndef SERVER_H
#define SERVER_H

#include "Request.h"

/**
 * @class Server
 * @brief The Server class represents a server in the load balancing system, responsible for processing incoming requests. Each Server object maintains its own state, including whether it is currently busy, the request it is processing, and the time remaining to complete the request.
 * The Server class provides methods to assign a new request to the server, process a cycle of work on the current request, check if the server is idle or done with its current request, and clear the completed request from the server's state.
 * This class is used by the LoadBalancer to manage the processing of requests across multiple servers and to determine when to scale up or down the number of active servers based on the load.
 */
class Server {
    private:
        int id;
        bool isBusy;
        Request* currReq;
        int time;
    public:
        /** 
         * @param id The unique identifier for the server. This ID can be used for logging and tracking purposes within the load balancing system.
         * The constructor initializes the server's state to idle (isBusy = false), sets the current request pointer to nullptr, and initializes the time remaining to process a request to zero. This ensures that when a Server object is created, it starts in a ready state, waiting to be assigned a request for processing.
         */
        Server(int id);

        /**
         * The destructor for the Server class is responsible for cleaning up any resources used by the Server object, such as the current request being processed. If the server is currently busy processing a request (i.e., currReq is not nullptr), the destructor will delete the Request object to free up memory and prevent memory leaks. This ensures that when a Server object is destroyed, it properly releases any resources it was using, maintaining good memory management practices in the load balancing system.
         */
        ~Server();

        /**
         * Checks if the server is currently idle, meaning it is not processing any request. This method returns true if the server is idle (i.e., not busy), and false if the server is currently processing a request.
         * The LoadBalancer can use this method to determine if a server is available to be assigned a new request.
         */
        bool isIdle();

        /**
            * @param r A pointer to the Request object to be processed by the server. The caller is responsible for managing the memory of the Request object, as it will be processed and deleted by the Server.
            * This method sets the server's state to busy, assigns the given Request pointer to the server's current request, and initializes the time remaining to process the request based on the time specified in the Request object.
            * The Server will then process this request over subsequent cycles until it is completed, at which point it can be cleared and made idle again.
        */
        void assign(Request* r);

        /**
         * Processes a cycle of work on the current request. If the server is busy processing a request, this method decrements the time remaining to complete the request. If the time reaches zero, the request is considered done, and the server can be cleared and made idle again.
         * This method should be called by the LoadBalancer during each cycle of processing to simulate the
         */
        void processCycle();

        /**
         * Checks if the server has completed processing its current request. If the server is busy and the time remaining to complete the request has reached zero, this method returns true, indicating that the request is done and the server can be cleared. Otherwise, it returns false.
         * This method allows the LoadBalancer to determine when a server has finished processing its current request
         */
        bool isDone();
        
        /**
         * Clears the completed request from the server's state, marking it as idle and resetting the time. This method should be called by the LoadBalancer when a server has finished processing its current request (as determined by the isDone method) to reset the server's state and allow it to accept new requests.
         * The method deletes the current Request object being processed by the server to free up memory and sets the server's state to idle, allowing it to be assigned a new request in subsequent cycles.
         */
        void clear();
};

#endif