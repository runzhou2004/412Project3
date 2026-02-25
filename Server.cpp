#include "Server.h"

Server::Server(int id): id(id), isBusy(false), currReq(nullptr) {}

Server::~Server() {
    delete currReq;
}

bool Server::isIdle() {
    return !isBusy;
}

void Server::assign(Request* r) {
    currReq = r;
    isBusy = true;
}

void Server::processCycle() {
    if (isBusy && currReq) {
        currReq->time--;
        if (currReq->time <= 0) isBusy = false;
    }
}

bool Server::isDone() {
    return !isBusy && currReq != nullptr;
}

void Server::clear() {
    delete currReq;
    currReq = nullptr;
}