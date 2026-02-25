#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

using namespace std;

class RequestQueue {
    private:
        queue<Request*> q;

    public:
        void enqueue(Request* r);
        Request* dequeue();
        bool empty();
        int size();
};

#endif