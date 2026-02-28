#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LoadBalancer.h"

using namespace std;

string randomIP() {
    return to_string(rand()%255) + "." + to_string(rand()%255) + "." + to_string(rand()%255) + "." + to_string(rand()%255);
}

int main() {
    srand(time(0));
    int servers;
    int runtime;

    cout << "Initial servers: ";
    cin >> servers;
    cout << "Runtime cycles: ";
    cin >> runtime;

    LoadBalancer lb(servers, 5);

    for (int i = 0; i < servers*100; i++) {
        lb.generateReq(new Request(randomIP(), randomIP(), rand()%10+1, (rand()%2 == 0 ? 'P' : 'S')));
    }

    for (int t = 0; t < runtime; t++) {
        if (rand()%5 == 0) {
            lb.generateReq(new Request(randomIP(), randomIP(), rand()%10+1, (rand()%2 == 0 ? 'P' : 'S')));
        }
        lb.processCycle();

        cout << "Cycle: " << t << endl;
        cout << "Servers: " << lb.getServerCount() << endl;
        cout << "Queue: " << lb.getQueueSize() << endl;
    }
}