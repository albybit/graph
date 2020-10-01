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
void ReadGraph(queue<string>&buffer,mutex& m,condition_variable& cv);
void Graph::init ( ifstream &stat){
    int v;
    unsigned eavg;
    char str[200];
    istringstream iss;
    string stri;

while(!stat.eof()) {
    stat.getline(str,200);
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
    nNodes=v;
roots.reserve(v);
 for(unsigned u=0;u<v;u++)
     roots.insert(u);
    e=e+nNodes;
    cscnode.csc_indices.reserve(v+1);
    cscnode.csc_nodes.reserve(e);
for (unsigned i=0;i<e;i++){
    cscnode.csc_nodes[i]=-1;
}
path.init(nNodes);

    for (unsigned i=0;i<nPartitions;i++)
    {
        nOfNodesProcessed[i]=0;

    }
    stri.clear();
}

Graph::Graph(ifstream &stat, ifstream &gra){
    unsigned i=0;
    init(stat);
    build(gra);
   numberOfNodesToProcess=roots.size();
  // printIt();
   divideJob();
   vector<thread> t;
   t.reserve(nPartitions);
   for (unsigned i=0;i<nPartitions;i++)
        t.push_back( thread([this,i]{compute_dfs_by_comparing_path(i); }));
for (unsigned i=0;i<nPartitions;i++)
    t[i].join();

}
void Graph::build(ifstream &gra) {
    unsigned u, v,pNodes=0;
    char *token;
    unsigned i = 0;
    unsigned counter=0;
    unsigned max_line_size = (log10(nNodes) + 2) * (nNodes + 1) + 3;
    char str[max_line_size];
    char dontcare[3];
    if (!gra.eof())
    gra.getline(str,max_line_size);

    while (!gra.eof()){

        gra.getline(str,max_line_size);


        // get the first token
        token = strtok(str, ":");
        if(token==NULL)
            break;
#if GRAPH_DEBUG
        printf( " \n%d", u );
#endif
       sscanf(token, "%d", &u);


       cscnode.csc_nodes[cscnode.i]=u;
       cscnode.csc_indices[cscnode.c]=cscnode.i;
       cscnode.i++;
       cscnode.c++;
        token = strtok(NULL, ":");
        sscanf(token,"%[^#]s",str);
      token = strtok(str, " ");
        //  walk through other tokens
         while (token!=NULL) {
            sscanf(token, "%d", &v);
             roots.erase(v);
         for (unsigned i=cscnode.csc_indices[u]+1;i<=cscnode.i;i++) {
             unsigned temp;

             if(cscnode.csc_nodes[i]>v){
                 temp=cscnode.csc_nodes[i];
                 cscnode.csc_nodes[i]=v;
                 v=temp;

             }
             else {
                 cscnode.csc_nodes[cscnode.i] = v;
             }
         }
            cscnode.i++;
         cscnode.csc_indices[cscnode.c+1]=cscnode.i;
#if GRAPH_DEBUG
             printf( " %d ", v);
#endif
        token=strtok(NULL," ");


         }

    }
    {
        unsigned i=roots.size()-1;
    rootsVector.reserve(roots.size());
        for (auto &elem: roots) {
            rootsVector[i]=elem;
            i--;

        }
    }
    }

 void Graph::compute_dfs_by_comparing_path(int threadIndex) {
   unsigned c=0;
   Path oldPath;
  path.Path::init(nNodes);
   oldPath.Path::init(nNodes);


 while(numberOfNodesToProcess>0)
   {
      unsigned left= partitions[threadIndex]+nOfNodesToProcess[threadIndex];
       mu[threadIndex].lock();
       for (unsigned i=partitions[threadIndex];i<left;i++) {
           nOfNodesProcessed[threadIndex]++;
          //  printf("%d thread, nodeprocessed:%d\n",threadIndex,rootsVector[i]);
             /*for(unsigned j=cscnode.csc_indices[rootsVector[i]];j<cscnode.csc_indices[rootsVector[i]+1];j++){
             }

                    //  oldPath.add(rootsVector[i], cscnode.csc_nodes[j]);
                      if (oldPath<path){
                   //       path=oldPath;
                      }
*/



       }


           mu[threadIndex].unlock();
              divideJob();
              divideJobM.lock();
              divideJobM.unlock();

   }

}

void Graph::divideJob() {
    unsigned i;
    if(!divideJobM.try_lock())
        return ;
for (i=0;i<nPartitions;i++) { // #TODO costruisci un ciclo esterno che cicla su quello interno attraverso cosi fai try lock
    mu[i].lock();
    cout<<nOfNodesProcessed[i];
    numberOfNodesToProcess = numberOfNodesToProcess - nOfNodesProcessed[i];
    nOfNodesProcessed[i]=0;
}
if (numberOfNodesToProcess<=0)
{
    divideJobM.unlock();
    return ;
}

    unsigned x= numberOfNodesToProcess/nPartitions;
  //  cout<<x<<endl;

    noOfNodesToProcessForEachThread=x;
for (i=0;i<nPartitions&& x>0;i++) {
    partitions[i] = i * x;
    nOfNodesToProcess[i]=x;

  //  cout<<partitions[i]<<" "<<x<<endl;
}
i=numberOfNodesToProcess%nPartitions;
if (i!=0){
    unsigned c=0;
    while (i>0){
        partitions[c+1]=partitions[c+1]+1;
        nOfNodesToProcess[c]+=1;
        i--;
        c++;
        if (c==nPartitions-1 && i>0){
            nOfNodesToProcess[c]+=1;
            i--;
            c=0;
        }
    }
}
for (i=0;i<nPartitions;i++)
    mu[i].unlock();
    divideJobM.unlock();
}

void Graph::printIt() {
}


