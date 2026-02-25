#include "RequestQueue.h"

void RequestQueue::enqueue(Request* r) {
    q.push(r);
}

Request* RequestQueue::dequeue() {
    if (q.empty()) return nullptr;
    Request* r = q.front();
    q.pop();
    return r;
}

bool RequestQueue::empty() {
    return q.empty();
}

int RequestQueue::size() {
    return q.size();
}