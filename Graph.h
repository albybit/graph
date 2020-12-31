#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <mutex>
#include <unordered_map>
#include <bits/stdc++.h>
#include "Barrier.h"
#define nPartitions 1
using namespace std;
struct path{
    int *path, sPath=10, lastElementIndex=0;

};
struct Node
{
    int id, visited= 0;
    int parent = -1, isItLeaf = -1, end = -1, subTreeSize= -1;
    struct path pt;
};
struct csc_Node{
    int *csc_nodes;
    int *csc_indices;
    int avg;

    int i=0, c=0;

};
struct  nodesAP{
    int i,j;
};
struct mn_linked{
    struct Node modifiednode;
    struct mn_linked *next;
    struct mn_linked *previous;
    int modified=-1,node; //it can be 0,1,2
};
struct mn{
    struct mn_linked *first,*last;
    struct mn_linked **array;

};
struct lf_linked{
    struct lf_linked *next,  *previous;
    int leaf=-1;

};
struct leaf_st{
    struct lf_linked ** array;
    struct lf_linked *first,*last;
    int numberofleafs=0;
};

struct rts_linked{
    struct rts_linked *next;
    struct rts_linked *previous; int node;
};
struct rts{
    struct rts_linked **array;
    struct rts_linked *first;
    struct rts_linked *last;
    int numberofroots=0;
};
class Graph {
    int nNodes;

    int  pre, post,prod,e;

    mutex divideJobM;
    int controlVariable=0;
    int synchroni=0;
    int numberOfNodesToProcess,noOfNodesToProcessForEachThread;
    struct mn modifiednodes[nPartitions];
    int *nedgesvisited[nPartitions];
    int *lengthOfArrayEdgesVisited;
    int *edgesvisited[nPartitions];
    vector< set<int> >edges;
    vector <set <int>> parents;
    vector< set<int> >incomingedges;
    int debug=0;
    struct Node *nodes;

    int numberOfroots;
    struct rts roots;
    struct rts **rootspointer;
    struct rts **rtsPartitions;
    struct nodesAP *clusters;
    int ncltrs=0;
   struct leaf_st leafs;
    set <int> notLeafs[nPartitions];
    int partitions[nPartitions]; //stores the index of the
    int nOfNodesToProcess[nPartitions];
    int nOfNodesProcessed[nPartitions];
    //vector<mutex> muxes;
    struct path rootsVector;
    struct csc_Node cscnode;
    vector<int> graph;
    vector<int> graph_csc; //compressed graph
    void divideJob(); // tested
    int anothercontrolvariable=0;
    void commitUpdates(); // tested
    void updateParent(int threadIndex,int node,int childnode);//tested
    int getPath(struct path *newpath,int threadIndex, int node);//tested
    void printIt();
    void countEdge(int threadIndex,int node);
    void computeClusters();
    void compute_dfs_by_comparing_path(int threadIndex);
    void test();
    void divideJobWrapper();
public:
    Graph(FILE  *stat, FILE  *gra);


    void InsertRoot(int u); //tested

    rts_linked *InsertRootInLinkedList(int u); //tested

    void InsertLeaf(int u);
  struct  lf_linked *InsertLeafInlinkedList(int u);


    void build(FILE *gra);

    void InsertEdge(int u, int v); //not to test

    void DeleteRoot(int i);//tested

    void init(FILE *stat);

    void assignPath(int index, int childnode, struct path vector); //tested

    void modifiednodesEmplace(int index, int node, int child_node, struct path newPath, int modified); //tested


    void insertRootsInArray();

    bool isEmpty(struct path *path); //tested

    bool IsPathLower(struct path *pt1, struct path *pt2); //tested

    void InitPath(struct path *p);
    void SubGraphSize(int threadIndex);
    void EmplaceNodeInPath(struct path *pPath, int node);
    void copyPath(struct path *pt1,struct path *pt2);

    void DeleteLeaf(const int &f);
};


#endif //GRAPH_GRAPH_H
