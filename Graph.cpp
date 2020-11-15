//
// Created by aberto on 26/08/20.
//

#include "Graph.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <queue>
#include <cmath>
#include <string>
#include <cstring>
#include <condition_variable>
#include "Path.h"
#include <boost/thread.hpp>
#include <thread>
#define GRAPH_DEBUG 0
#include <chrono>
void Graph::init ( FILE *stat){
    int v;
    unsigned eavg;
    char str[2000];
    string stri;

 while(       fgets(str,2000,stat)!=NULL){
stri=str;

if (stri.find("|V|")!=string::npos) {
    std::size_t const n = stri.find_first_of("0123456789");
    if (n != std::string::npos)
    {
        std::size_t const m = stri.find_first_not_of("0123456789", n);
        v=stoi(stri.substr(n, m != std::string::npos ? m-n : m)); //extract number from a string
    }
}
    if (stri.find("|Eavg|")!=string::npos){

        std::size_t const n = stri.find_first_of("0123456789");
        if (n != std::string::npos)
        {
            std::size_t const m = stri.find_first_not_of("0123456789", n);
            eavg=stoi(stri.substr(n, m != std::string::npos ? m-n : m)); //extract number from a string
        }
    }

if(stri.find("|E|")!=string::npos) {
    std::size_t const n1 = stri.find_first_of("0123456789");
    if (n1 != std::string::npos) {
        std::size_t const m = stri.find_first_not_of("0123456789", n1);
        e = stoi(stri.substr(n1, m != std::string::npos ? m - n1 : m));
    }
}}
 modifiedparents.reserve(nPartitions);
 edgesVisited.reserve(nPartitions);
 modifiedVectors.reserve(nPartitions
         );
for (unsigned i=0;i<nPartitions;i++){
    map<unsigned,unsigned> e;
    map<unsigned,vector<unsigned>> v;
    map<unsigned,unsigned> c;
    edgesVisited.push_back(e);
    modifiedVectors.push_back(v);
    modifiedparents.push_back(c);
}

    nNodes=v;
roots.reserve(v);
edges.reserve(nNodes);
edgesVisited.reserve(nNodes);
 for(unsigned u=0;u<v;u++) {
     roots.insert(u);
     set<int> c = set<int>();
     edges.emplace_back(c);
nodes[u].path;
edgesVisited.reserve(nPartitions);
 }
    e=e+nNodes;
    cscnode.csc_indices=(unsigned*)malloc(sizeof(unsigned)*(v+1));
    cscnode.csc_nodes=(unsigned*)malloc(sizeof(unsigned)*(e*2));
for (unsigned i=0;i<e*2;i++){
    cscnode.csc_nodes[i]=-1;
}
    for (unsigned i=0;i<nPartitions;i++)
    {
        nOfNodesProcessed[i]=0;

    }
    stri.clear();
   clusters=(struct nodesAP*)malloc(sizeof(struct nodesAP)*roots.size());
    for (unsigned i=0;i<roots.size();i++) {
        clusters[i].i = -1;
        clusters[i].j=-1;
    }
    for (unsigned i=0;i<nPartitions;i++) {
        partitions[i] = 0;
    }

}
void Graph::test()
{

}
Graph::Graph(FILE *stat, FILE *gra){
    unsigned i=0;
    init(stat);
    build(gra);
    numberOfNodesToProcess=roots.size();

    divideJobWrapper();
    test();
    /*printIt();
    i=clusters[0].i;
    clusters[0].i=20g;
    nOfNodesProcessed[0]=clusters[0].i-i;

    i=clusters[1].i;
    clusters[1].i=36;
    nOfNodesProcessed[1]=clusters[1].i-i;

    i=clusters[2].i;
    clusters[2].i=54;
    nOfNodesProcessed[2]=clusters[2].i-i;

    i=clusters[3].i;
    clusters[3].i=67;
    nOfNodesProcessed[3]=clusters[3].i-i;
   for (unsigned i=0;i<nPartitions;i++)
       cout<<nOfNodesProcessed[i]<<endl;

    numberOfNodesToProcess=roots.size();
     divideJob();
*/
  vector<thread> t;
  t.reserve(nPartitions);
    auto t1 = std::chrono::high_resolution_clock::now();
   for (unsigned i=0;i<nPartitions;i++)
            t.push_back( thread( [this, i] { compute_dfs_by_comparing_path(i); }));
for (unsigned i=0;i<nPartitions;i++)
    t[i].join();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout<<"time "<<duration;

}
void Graph::build(FILE *gra) {
    unsigned u, v,pNodes=0;
    char *token;
    unsigned i = 0;
    unsigned counter=0;
    char str[2000];
    char dontcare[3];
    if (gra!=NULL)
    fgets(str,2000,gra);

    while (fgets(str,2000,gra)!=NULL){



        // get the first token
        token = strtok(str, ":");
        if(token==NULL)
            break;
#if GRAPH_DEBUG
        printf( " \n%d", u );
#endif
       sscanf(token, "%d", &u);


        token = strtok(NULL, ":");
        sscanf(token,"%[^#]s",str);
      token = strtok(str, " ");
        //  walk through other tokens
         while (token!=NULL) {
            sscanf(token, "%d", &v);
             roots.erase(v);

             edges[u].insert(v);
             edges[v].insert(u);


#if GRAPH_DEBUG
             printf( " %d ", v);
#endif
        token=strtok(NULL," ");
         }

    }
    {

        for (unsigned z=0;z<nNodes;z++){

            cscnode.csc_nodes[cscnode.i]=z;
            cscnode.csc_indices[cscnode.c]=cscnode.i;
            cscnode.c++;
            cscnode.i++;
            auto it=edges[z].begin();
             for (set<int>::iterator it= edges[z].cbegin();!edges[z].empty()&& it!=edges[z].cend() ;it++){

               cscnode.csc_nodes[cscnode.i] = *it;
               cscnode.i++;
           }
            cscnode.csc_indices[cscnode.c]=cscnode.i;
        }
        cscnode.csc_nodes[cscnode.i]=nNodes;
        cscnode.csc_indices[cscnode.c]=cscnode.i;

    }
    {
        unsigned i=roots.size()-1;

    }
    vector<Node> to_swap(nNodes);
    nodes.swap(to_swap);

}
int Graph::getPath(vector<unsigned> &path,unsigned threadIndex,unsigned node) {
    if (modifiedVectors[threadIndex].find(node)!=modifiedVectors[threadIndex].end()){
        path=modifiedVectors[threadIndex].find(node)->second;
        return 1;
    }else{
        if (nodes[node].path.empty()){
            return 2;
        }
        else{
          path=nodes[node].path;
          return 3;
        }
    }

}
 void Graph::compute_dfs_by_comparing_path(int threadIndex) {
   unsigned i,in1,in2,c=threadIndex,node,ok,childnode;
   vector<unsigned> oldpath,newpath;

   i=0;
     while(rootsVector.size()>0){
         mu[threadIndex].lock();
     while(nOfNodesToProcess[threadIndex]>0){
         while(clusters[c].i>=clusters[c].j)c++;
       node=rootsVector[clusters[c].i];
       clusters[c].i++;
       in1=cscnode.csc_indices[rootsVector[clusters[c].i]]+1;
       in2=cscnode.csc_indices[rootsVector[clusters[c].i]+1];
       ok=getPath(newpath,threadIndex,node);
     if (  ok==2){newpath.emplace_back(node);
     modifiedVectors[threadIndex].emplace(node,newpath);
     }
       for (unsigned z=in1;z<in2;z++){
          childnode=cscnode.csc_nodes[z];
           newpath.emplace_back(childnode);
           ok=getPath(oldpath,threadIndex,childnode);
               switch (ok) {
                   case 1:
                       if(oldpath>newpath) {
                          modifiedVectors[threadIndex].find(childnode)->second = newpath;
                          countEdge(threadIndex,childnode);
                           updateParent(threadIndex,node,childnode);
                       }
                       break;
                   case 2:
                       modifiedVectors[threadIndex].emplace(childnode,newpath);
                      countEdge(threadIndex,childnode);
                      updateParent(threadIndex,node,childnode);
                       break;
                   case 3:
                       if (oldpath>newpath){
                          modifiedVectors[threadIndex].emplace(childnode,newpath);
                          countEdge(threadIndex,childnode);
                          updateParent(threadIndex,node,childnode);
                       }

                           break;

               }

            newpath.pop_back();
       }


         i++;
      nOfNodesToProcess[threadIndex]--;
      nOfNodesProcessed[threadIndex]++;
       clusters[c].i++;
     }
     mu[threadIndex].unlock();

     divideJobWrapper();
     divideJobM.lock();
     divideJobM.unlock();
 }
}
void Graph::commitUpdates(){
    controlVariable=0;
    for (unsigned i=0;i<nPartitions;i++){
    for (map<unsigned,unsigned>::iterator it =modifiedparents[i].begin();it!=modifiedparents[i].end();it++ )
        nodes[it->first].parent=it->second;
   for (map<unsigned,vector<unsigned>>::iterator it=modifiedVectors[i].begin();it!=modifiedVectors[i].end();it++)
       nodes[it->first].path=it->second;
   nOfNodesProcessed[i]=0;
    }

}
void Graph::updateParent(unsigned threadIndex,unsigned node,unsigned childnode){
  if( modifiedparents[threadIndex].find(childnode)==modifiedparents[threadIndex].end())
      modifiedparents[threadIndex].emplace(childnode,node);
  else
      modifiedparents[threadIndex].find(childnode)->second=node;
}
void Graph::countEdge(unsigned threadIndex,unsigned node){
   if (edgesVisited[threadIndex].find(node)==edgesVisited[threadIndex].end())
       edgesVisited[threadIndex].emplace(node,1);
   else
       edgesVisited[threadIndex].find(node)->second++;

}
void Graph::divideJobWrapper(){
    if (!divideJobM.try_lock())
    {
        divideJobM.lock();
        divideJobM.unlock();
        return;
    }
        for (unsigned i=0;i<nPartitions;i++)
            mu[i].lock();
divideJob();
    for (unsigned i=0;i<nPartitions;i++)
        mu[i].unlock();
    divideJobM.unlock();

}
void Graph::divideJob() {
    unsigned i;

for (i=0;i<nPartitions;i++) { // #TODO costruisci un ciclo esterno che cicla su quello interno attraverso cosi fai try lock
    numberOfNodesToProcess = numberOfNodesToProcess - nOfNodesProcessed[i];
    nOfNodesProcessed[i]=0;
    nOfNodesToProcess[i]=0;
}
if (numberOfNodesToProcess<0)
{
    divideJobM.unlock();
    return ;
}

    unsigned x= numberOfNodesToProcess/nPartitions;
    noOfNodesToProcessForEachThread=x;

if (controlVariable==0) {

    ncltrs=nPartitions;
 controlVariable=1;
    for (i = 0; i < nPartitions && x > 0; i++) {

        clusters[i].i=partitions[i] = i * x;
        clusters[i].j=noOfNodesToProcessForEachThread+clusters[i].i;

        nOfNodesToProcess[i] = x;    // printIt();
    }
i=numberOfNodesToProcess%nPartitions;

    nOfNodesToProcess[0]+=i;
    clusters[0].j+=i;

    for (unsigned c=1;c<nPartitions;c++)
    {
        partitions[c]+=i;
        clusters[c].i+=i;
        clusters[c].j+=i;
    }
}else{
    computeClusters();
}
}

void Graph::printIt() {
    for (unsigned z=0;z<nNodes;z++) {
     if (!nodes[z].path.empty())
        cout << nodes[z].path[nodes[z].path.size() - 1] << endl;
    }
    }
void Graph::computeClusters() {
    unsigned remaining = numberOfNodesToProcess % nPartitions;
   int tmpI = -1, tmpJ = -1, newI, newJ, c = 0, x = 1;
    for (unsigned i = 0; i < nPartitions && noOfNodesToProcessForEachThread > 0; i++) {
        while (clusters[c].i == clusters[c].j && clusters[c].i != -1)
            c++;
        partitions[i] = clusters[c].i;

        newI = clusters[c].i + noOfNodesToProcessForEachThread + remaining;
        nOfNodesToProcess[i] = noOfNodesToProcessForEachThread + remaining;
        if (remaining != 0)
            remaining = 0;
        while (newI > clusters[c].j && clusters[c].j != -1) {
            c++;
            newI = newI - clusters[c - 1].j + clusters[c].i;
        }
        if (clusters[c].j != newI) {
            x = c;
            newJ=clusters[x].j;
            clusters[x].j=newI;
            while (x <ncltrs) {
                x++;
                if (ncltrs== x) {
                    clusters[x].j=newJ;
                    clusters[x].i=newI;
                    c++;
                    ncltrs++;
                    break;
                }
                tmpI = clusters[x].i;
                tmpJ = clusters[x].j;
                clusters[x].j=newJ;
                clusters[x].i=newI;
                newI = tmpI;
                newJ=tmpJ;
            }

        }else{c++;
             }
    }
}




