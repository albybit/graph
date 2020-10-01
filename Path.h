//
// Created by aberto on 24/09/20.
//

#ifndef GRAPH_PATH_H
#define GRAPH_PATH_H
#include "Graph.h"
class Path{
private:
    int *reserved[2];
    int *pathTail[nPartitions-2];
    int n;
public:
    Path(){
        reserved[0]={0};
        reserved[1]={0};
    };
    void print();
    bool  operator<(const Path &p);
    Path& operator=(const Path &newPath);
void init(int n);
    void add( const unsigned u,
             const unsigned v);

};

#endif //GRAPH_PATH_H
