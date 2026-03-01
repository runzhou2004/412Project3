#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

using namespace std;

/**
 * @class RequestQueue
 * @brief The RequestQueue class manages a queue of Request objects, providing methods to enqueue new requests, dequeue requests for processing, check if the queue is empty, and get the current size of the queue.
 * The RequestQueue class serves as a fundamental component in the load balancing system, allowing for efficient management of incoming requests as they are processed by the servers in the LoadBalancer.
 * It encapsulates the underlying data structure (a standard queue) and provides a simple interface for interacting with the queue of requests.
 */
class RequestQueue {
    private:
        queue<Request*> q;

    public:
        /**
         * Enqueues a new Request object into the queue. The request is added to the back of the queue, following the First-In-First-Out (FIFO) principle.
         * @param r A pointer to the Request object to be enqueued. The caller is responsible for managing the memory of the Request object, as it will be processed and deleted by the LoadBalancer.
         * This method adds the given Request pointer to the end of the internal queue, allowing it to be processed in order as requests are dequeued.
         */
        void enqueue(Request* r);

        /**
         * Dequeues a Request object from the front of the queue for processing. The method returns a pointer to the Request object that is being processed, or nullptr if the queue is empty.
         * @return A pointer to the Request object at the front of the queue, or nullptr if the queue is empty. The caller is responsible for managing the memory of the returned Request object, as it will be processed and deleted by the LoadBalancer.
         * This method removes and returns the Request pointer at the front of the internal queue, allowing it to be processed by a server in the LoadBalancer. If the queue is empty, it returns nullptr to indicate that there are no requests to process.
         */
        Request* dequeue();

        /**
         * Checks if the queue is empty, indicating that there are no requests waiting to be processed.
         * @return true if the queue is empty, false otherwise. This method allows the LoadBalancer to determine if there are any pending requests that need to be processed.
         */
        bool empty();

        /**
         * Gets the current size of the queue, indicating how many requests are waiting to be processed.
         * @return The number of Request objects currently in the queue. This method allows the LoadBalancer to monitor the load on the system and make decisions about scaling servers based on the number of pending requests.
         */
        int size();
};

#endif