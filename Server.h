#ifndef SERVER_H
#define SERVER_H

#include "Request.h"

class Server {
    private:
        int id;
        bool isBusy;
        Request* currReq;
        int time;
    public:
        Server(int id);
        ~Server();

        bool isIdle();
        void assign(Request* r);
        void processCycle();
        bool isDone();
        void clear();
};

#endif