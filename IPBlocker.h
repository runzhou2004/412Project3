#ifndef IPBLOCKER_H
#define IPBLOCKER_H

#include <vector>
#include <string>

using namespace std;

/**
 * @class IPBlocker
 * @brief The IPBlocker class is responsible for managing a list of blocked IP address ranges
 * and providing functionality to check if a given IP address is blocked. It allows adding ranges of IP addresses to the block list and checking if a specific IP address falls within any of the blocked ranges.
 * The IPBlocker class uses a vector of pairs to store the blocked IP ranges, where each pair consists of a starting IP address and an ending IP address. The isBlocked method iterates through the list of blocked ranges and checks if the given IP address falls within any of the ranges by comparing it to the start and end of each range.
 * Note: This implementation assumes that the IP addresses are in a format that allows for simple string comparison (e.g., "
 * This class is not optimized for performance, as it checks each range sequentially. For a large number of blocked ranges, a more efficient data structure (e.g., a trie or a binary search tree) could be used to improve lookup times.
 * The IPBlocker class is a crucial component of the load balancing system, as it helps to prevent malicious or unwanted traffic from reaching the servers by blocking specific IP addresses or ranges of IP addresses.
 */
class IPBlocker {
    private:
        vector<pair<string, string>> ranges;

    public:
        /**
         * Adds a range of IP addresses to the block list. The start and end parameters define the range of IPs to block.
         * For example, addRange("192.168.1.0", "192.168.1.255")
         * @param start The starting IP address of the range to block.
         * @param end The ending IP address of the range to block.
         * This method does not perform any validation on the input IP addresses, so it is assumed that they are in a valid format and that the start IP is less than or equal to the end IP.
         * The ranges are stored in a vector of pairs, where each pair represents a blocked range of IP addresses.
         * The isBlocked method will check if a given IP address falls within any of the blocked ranges by comparing the IP address to the start and end of each range.
         * Note: This implementation is not optimized for performance, as it checks each range sequentially. For a large number of blocked ranges, a more efficient data structure (e.g., a trie or a binary search tree) could be used to improve lookup times.
         */
        void addRange(string start, string end);

        /**
         * Checks if a given IP address is blocked by comparing it against the list of blocked ranges.
         * @param ip The IP address to check, represented as a string (e.g., "
         * @return true if the IP address is blocked, false otherwise.
         * The method iterates through the list of blocked ranges and checks if the given IP address
         * falls within any of the ranges by comparing it to the start and end of each range. If a match is found, it returns true; if no matches are found after checking all ranges, it returns false.
         * Note: This method assumes that the IP addresses are in a format that allows for simple string comparison (e.g., "
         */ 
        bool isBlocked(string ip);
};

#endif