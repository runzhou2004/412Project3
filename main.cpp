#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Config.h"
#include "LoadBalancer.h"
#include "Switch.h"


using namespace std;

string randomIP() {
    return to_string(rand()%255) + "." + to_string(rand()%255) + "." + to_string(rand()%255) + "." + to_string(rand()%255);
}

int main() {
    srand(time(0));
    int servers;
    int runtime;
    int restCycles;

    // cout << "Initial servers: ";
    // cin >> servers;
    // cout << "Runtime cycles: ";
    // cin >> runtime;

    Config config("config.txt");
    servers = config.getInitialServers();
    runtime = config.getRuntime();
    restCycles = config.getRestCycles();

    ofstream logFile("log.txt");
    
    LoadBalancer processingLB(servers, restCycles, logFile);
    LoadBalancer streamingLB(servers, restCycles, logFile);

    int startingProcessQueue = processingLB.getQueueSize();
    int startingStreamQueue = streamingLB.getQueueSize();

    Switch systemSwitch(&processingLB, &streamingLB);

    for (int i = 0; i < servers*100; i++) {
        systemSwitch.routeRequest(new Request(randomIP(), randomIP(), rand()%10+1, 'P'));
        systemSwitch.routeRequest(new Request(randomIP(), randomIP(), rand()%10+1, 'S'));
    }

    for (int t = 0; t < runtime; t++) {
        if (rand()%5 == 0) {
            systemSwitch.routeRequest(new Request(randomIP(), randomIP(), rand()%10+1, 'P'));
            systemSwitch.routeRequest(new Request(randomIP(), randomIP(), rand()%10+1, 'S'));
        }
        processingLB.processCycle();
        streamingLB.processCycle();

        if (t % 1000 == 0) {
            logFile << "------------------------------" << endl;
            logFile << "Cycle: " << t+1 << endl;
            logFile << "Processing Servers: " << processingLB.getServerCount() << endl;
            logFile << "Processing Queue: " << processingLB.getQueueSize() << endl;
            logFile << "Completed (Processing): " << processingLB.getProcessedRequests() << endl;
            logFile << "Streaming Servers: " << streamingLB.getServerCount() << endl;
            logFile << "Streaming Queue: " << streamingLB.getQueueSize() << endl;
            logFile << "Completed (Streaming): " << streamingLB.getProcessedRequests() << endl;
            
        }
    }
        logFile << "==============================" << endl;
        logFile << "Summary:" << endl;
        logFile << "Initial Servers (Processing): " << servers << endl;
        logFile << "Initial Servers (Streaming): " << servers << endl;
        logFile << "Runtime Cycles: " << runtime << endl;
        logFile << "Rest Cycles: " << restCycles << endl;
    
        logFile << "------------------------------" << endl;
        logFile << "Starting Queue Size (Processing): " << startingProcessQueue << endl;
        logFile << "Starting Queue Size (Streaming): " << startingStreamQueue << endl;

        logFile << "------------------------------" << endl;
        logFile << "Final Queue Size (Processing): " << processingLB.getQueueSize() << endl;
        logFile << "Final Queue Size (Streaming): " << streamingLB.getQueueSize() << endl;

        logFile << "------------------------------" << endl;
        logFile << "Range for task times: 1-10 cycles" << endl;

        logFile << "------------------------------" << endl;
        logFile << "Total Requests Generated: " << processingLB.getGeneratedRequests() + streamingLB.getGeneratedRequests() << endl;
        logFile << "Total Requests Processed: " << processingLB.getProcessedRequests() + streamingLB.getProcessedRequests() << endl;
        logFile << "Total Blocked Requests: " << processingLB.getBlockedRequests() + streamingLB.getBlockedRequests() << endl;

        logFile << "------------------------------" << endl;
        logFile << "Total Servers Added (Processing): " << processingLB.getServersAdded() << endl;
        logFile << "Total Servers Removed (Processing): " << processingLB.getServersRemoved() << endl;
        logFile << "Total Servers Added (Streaming): " << streamingLB.getServersAdded() << endl;
        logFile << "Total Servers Removed (Streaming): " << streamingLB.getServersRemoved() << endl;

        logFile << "------------------------------" << endl;
        logFile << "Max Queue Size (Processing): " << processingLB.getMaxQueueSize() << endl;
        logFile << "Max Queue Size (Streaming): " << streamingLB.getMaxQueueSize() << endl;
        logFile << "==============================" << endl;
    
    logFile.close();
}