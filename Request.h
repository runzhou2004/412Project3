/**
 * @file Request.h
 * @brief The Request struct represents an incoming request to the load balancer, containing information about
 * the source and destination IP addresses, the time required to process the request, and the type of job (e.g., 'P' for processing or 'S' for storage). The Request struct is used to encapsulate the details of a request and is passed through the system as it is processed by the servers in the load balancer. It serves as a fundamental data structure for managing and processing incoming requests in the load balancing system.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

/**
 * @struct Request
 * @brief The Request struct represents an incoming request to the load balancer, containing information about the source and destination IP addresses, the time required to process the request, and the type of job (e.g., 'P' for processing or 'S' for storage).
 * The Request struct is used to encapsulate the details of a request and is passed through the system as it is processed by the servers in the load balancer.
 * It serves as a fundamental data structure for managing and processing incoming requests in the load balancing system.
 */
struct Request {
    string ipIn;
    string ipOut;
    int time;
    char jobType;

    // Constructor to initialize a Request object with the given parameters.
    Request(string in, string out, int time, char type)
        : ipIn(in), ipOut(out), time(time), jobType(type) {}
};

#endif