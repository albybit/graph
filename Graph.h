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
#define nPartitions 4
#include "Path.h"
#define MATRIX 0
using namespace std;
struct Node
{
    unsigned id, inc_visited_count = 0;
    int parent = -1, start = -1, end = -1, subTreeSize= -1;
   // vector<unsigned > adj;
    //unordered_map<unsigned, bool> inc;
    /*vector<unsigned> inc;
    vector<bool> inc_visited;
     */
    bool no_path = true;
    bool visited = false;
   // vector<unsigned> path;
  //  mutex mux;

};

struct csc_Node{
    vector<unsigned>csc_nodes;
    vector<unsigned>csc_indices;
    unsigned avg;

    vector<unsigned> nEdges;
    unsigned i=0, c=0;

};
class Graph {
unsigned nNodes;
    unsigned  pre, post,prod,e;
    mutex mu[nPartitions];
    mutex divideJobM;
    unsigned numberOfNodesToProcess,noOfNodesToProcessForEachThread;
    Path path;

    unsigned partitions[nPartitions]; //stores the index of the
    unsigned nOfNodesToProcess[nPartitions];
    unsigned nOfNodesProcessed[nPartitions];
    //vector<mutex> muxes;
    vector<Node> nodes;
    unordered_set<unsigned> roots;
    vector<unsigned> rootsVector;
   struct csc_Node cscnode;

#if MATRIX
vector<vector<bool>> graph;
#else
vector<int> graph;
vector<int> graph_csc; //compressed graph
#endif
void init(ifstream &stat);
void build(ifstream &gra);
void divideJob();
void printIt();
     void compute_dfs_by_comparing_path(int threadIndex);
public:
    Graph(ifstream &stat, ifstream &gra);


};


#endif //GRAPH_GRAPH_H
