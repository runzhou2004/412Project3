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
    
    LoadBalancer processingLB(servers, restCycles);
    LoadBalancer streamingLB(servers, restCycles);

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

        cout << "Cycle: " << t+1 << endl;
        cout << "Processing Servers: " << processingLB.getServerCount() << endl;
        cout << "Processing Queue: " << processingLB.getQueueSize() << endl;
        cout << "Streaming Servers: " << streamingLB.getServerCount() << endl;
        cout << "Streaming Queue: " << streamingLB.getQueueSize() << endl;
        logFile << "Cycle: " << t+1 << endl;
        logFile << "Processing Servers: " << processingLB.getServerCount() << endl;
        logFile << "Processing Queue: " << processingLB.getQueueSize() << endl;
        logFile << "Streaming Servers: " << streamingLB.getServerCount() << endl;
        logFile << "Streaming Queue: " << streamingLB.getQueueSize() << endl;
    }
    logFile.close();
}