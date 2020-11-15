//
// Created by aberto on 24/09/20.
//

#ifndef GRAPH_PATH_H
#define GRAPH_PATH_H
#include "Graph.h"
using namespace std;
class Path{
private:
    vector<vector<unsigned>> path;
public:
    Path(int n){
        path.reserve(n);
    };
    void print();
    bool  operator<(const Path &p);
    Path& operator=(const Path &newPath);
    void add( const unsigned u,
             const unsigned v);

};

#endif //GRAPH_PATH_H
