#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

struct Request {
    string ipIn;
    string ipOut;
    int time;
    char jobType;

    Request(string in, string out, int time, char type)
        : ipIn(in), ipOut(out), time(time), jobType(type) {}
};

#endif