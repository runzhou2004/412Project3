#include "IPBlocker.h"

using namespace std;

void IPBlocker::addRange(string start, string end) {
    ranges.push_back({start,end});
}

bool IPBlocker::isBlocked(string ip) {
    for (auto& r:ranges) {
        if (ip >= r.first && ip <= r.second) {
            return true;
        }
    }
    return false;
}