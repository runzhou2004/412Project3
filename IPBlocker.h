#ifndef IPBLOCKER_H
#define IPBLOCKER_H

#include <vector>
#include <string>

using namespace std;

class IPBlocker {
    private:
        vector<pair<string, string>> ranges;

    public:
        void addRange(string start, string end);
        bool isBlocked(string ip);
};

#endif