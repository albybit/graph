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
using namespace std;
struct path{
    int *path, sPath=0, lastElementIndex=0;
};
struct Node
{
    unsigned id, inc_visited_count = 0;
    int parent = -1, start = -1, end = -1, subTreeSize= -1;
   struct path *pt;

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
struct mn_linked{
    struct Node;
    struct mn_linked *next;
    struct mn_linked *previous;
    struct mn_linked *array;
    int modified=-1; //it can be 0,1,2
};
struct mp_linked{
    struct mp_linked* next;
    struct mp_linked* previous;
    int node=-1,newParent=-1;

};
struct mp{
    struct mp_linked *first;
    struct mp_linked **array;
    struct mp_linked *last;

};
struct mv_linked{
    struct mv_linked *next;
    struct mv_linked *previous;
    int node;
  struct path *newPath;
};
struct mv{
    struct mv_linked **array;
    struct mv_linked *first;
    struct mv_linked *last;

};
struct sz{
    int mp,mv,ev;
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
    unsigned nNodes;

    unsigned  pre, post,prod,e;
    mutex mu[nPartitions];
    mutex divideJobM;
    unsigned controlVariable=0;
    unsigned numberOfNodesToProcess,noOfNodesToProcessForEachThread;
    struct mp modifiedparents[nPartitions];
    struct mv modifiedVectors[nPartitions];
    int *nedgesvisited[nPartitions];
    int lengthOfArrayEdgesVisited[nPartitions];
    int *edgesvisited[nPartitions];
    vector< set<int> >edges;
    struct Node *nodes;
    struct sz *size;

    int numberOfroots;
    struct rts roots;
    struct rts **rootspointer;
    struct rts **rtsPartitions;
    struct nodesAP *clusters;
    unsigned ncltrs=0;
    unsigned partitions[nPartitions]; //stores the index of the
    unsigned nOfNodesToProcess[nPartitions];
    unsigned nOfNodesProcessed[nPartitions];
    //vector<mutex> muxes;
    vector<unsigned> rootsVector;
    struct csc_Node cscnode;
    vector<int> graph;
    vector<int> graph_csc; //compressed graph


    void divideJob();
    int anothercontrolvariable=0;
    void commitUpdates();
    void updateParent(unsigned threadIndex,unsigned node,unsigned childnode);
    int getPath(struct path *newpath,unsigned threadIndex, unsigned node);
    void printIt();
    void countEdge(unsigned threadIndex,unsigned node);
    void computeClusters();
    void compute_dfs_by_comparing_path(int threadIndex);
    void test();
    void divideJobWrapper();
public:
    Graph(FILE  *stat, FILE  *gra);


    void InsertRoot(unsigned int u);

    rts_linked *InsertRootInLinkedList(unsigned int u);


    void build(FILE *gra);

    void InsertEdge(unsigned int u, unsigned int v);

    void DeleteRoot(unsigned int i);

    void init(FILE *stat);

    void assignPath(int index, unsigned int childnode, struct path *vector);

    void modifiedVectorsEmplace(int index, unsigned int node, struct path *newPath);

    void modifiedParentsEmplace(unsigned index, unsigned node, unsigned child_node);


    void emplacenodeinpath(int node,struct path *pt);
    void insertRootsInArray();

    void initPath(path *pt);
    void popBackFromPath(struct path *pt);
    int isOldBigger(path *opt, path *npt);
};


#endif //GRAPH_GRAPH_H
