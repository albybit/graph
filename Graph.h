//
// Created by aberto on 26/08/20.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <mutex>
#include <unordered_map>
#include <bits/stdc++.h>
#define nPartitions 4
#include "Path.h"
#define MATRIX 0
#define CSCNODES 1
using namespace std;
struct Node
{
    unsigned id, inc_visited_count = 0;
    int parent = -1, start = -1, end = -1, subTreeSize= -1;
    /*vector<unsigned> inc;
    vector<bool> inc_visited;
     */
    vector<unsigned> path;

};
struct csc_Node{
    unsigned *csc_nodes;
    unsigned *csc_indices;
    unsigned avg;

    unsigned i=0, c=0;

};
struct  nodesAP{
    int i,j;
};
class Graph {
unsigned nNodes;

    unsigned  pre, post,prod,e;
    mutex mu[nPartitions];
    mutex divideJobM;
    unsigned controlVariable=0;
    unsigned numberOfNodesToProcess,noOfNodesToProcessForEachThread;
vector<set<int> > edges;
   vector <map<unsigned,unsigned>> modifiedparents;
   vector< map<unsigned/*nodo*/,vector<unsigned>/*path nodo*/ >> modifiedVectors;
   /*modifiedVectors[0] primo thread, modifiedVectors[1] secondo thread, modifiedVectors[2] terzo thread...*/
    vector<map<unsigned/*nodo*/,unsigned/*numero degli archi uscenti/entranti visitati*/>> edgesVisited; // we use it for alg 4
   /*edgesVisited[0] primo thread, edgesVisited[1] secondo thread, edgesVisited[2] terzo thread...*/
    vector<struct Node> nodes;
    struct nodesAP *clusters;
    unsigned ncltrs=0;
    unsigned partitions[nPartitions]; //stores the index of the
    unsigned nOfNodesToProcess[nPartitions];
    unsigned nOfNodesProcessed[nPartitions];
    //vector<mutex> muxes;
    unordered_set<unsigned> roots;
    vector<unsigned> rootsVector;
   struct csc_Node cscnode;
#if MATRIX
vector<vector<bool>> graph;
#else
vector<int> graph;
vector<int> graph_csc; //compressed graph
#endif
void init(FILE  *stat);
void build(FILE  *gra);
void divideJob();

    void Graph::commitUpdates();
void updateParent(unsigned threadIndex,unsigned node,unsigned childnode);
 int getPath(vector<unsigned>&path,unsigned threadIndex, unsigned node);
void printIt();
void countEdge(unsigned threadIndex,unsigned node);
void computeClusters();
     void compute_dfs_by_comparing_path(int threadIndex);
void test();
    void divideJobWrapper();
public:
    Graph(FILE  *stat, FILE  *gra);


};


#endif //GRAPH_GRAPH_H
