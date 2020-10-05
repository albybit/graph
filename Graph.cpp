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
   clusters=(struct nodesAP*)malloc(sizeof(struct nodesAP)*roots.size());
    for (unsigned i=0;i<roots.size();i++) {
        clusters[i].i = -1;
        clusters[i].j=-1;
    }
    for (unsigned i=0;i<nPartitions;i++) {
        partitions[i] = 0;
    }
}

Graph::Graph(ifstream &stat, ifstream &gra){
    unsigned i=0;
    init(stat);
    build(gra);
   numberOfNodesToProcess=roots.size();
   divideJob();
    // printIt();
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
     while(nOfNodesToProcess[threadIndex]>0)
   {
     mu[threadIndex].lock();
         unsigned right = nOfNodesToProcess[threadIndex] + partitions[threadIndex];
     for (unsigned i=partitions[threadIndex];i<right;i++) {

         nOfNodesProcessed[threadIndex]++;
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
    numberOfNodesToProcess = numberOfNodesToProcess - nOfNodesProcessed[i];
    nOfNodesProcessed[i]=0;
    nOfNodesToProcess[i]=0;
}
if (numberOfNodesToProcess<=0)
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
        cout << partitions[i] << " " << partitions[i] + nOfNodesToProcess[i] << endl;
    }
i=numberOfNodesToProcess%nPartitions;
    unsigned c=0;
if (i!=0){
    while    (i>0){
        partitions[c+1]=partitions[c+1]+1;
        clusters[c+1].i=partitions[c+1]+1;
        clusters[c].j++;
for (unsigned k=c+1;k<nPartitions;k++){
	clusters[c].i++;
	clusters[c].j++;
	}
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
}else{
    computeClusters();
}
for (i=0;i<nPartitions;i++)
    mu[i].unlock();
    divideJobM.unlock();
}

void Graph::printIt() {
}
void Graph::computeClusters(){
  unsigned remaining= numberOfNodesToProcess%nPartitions;
  unsigned tmpI=-1,tmpJ=-1,newI,newJ,c=0,x=1;

  for (unsigned i=0;i<nPartitions && noOfNodesToProcessForEachThread>0;i++) {
          newJ = clusters[c].i + numberOfNodesToProcess;
          while(newJ>clusters[c].j && clusters[c].j!=-1){
              c++;
              if (clusters[c].j>newJ)
              newJ=newJ-clusters[c-1].j+clusters[c].i;
          }
          x=c;

      newI=newJ;
      while(x<=ncltrs ){
             newJ=clusters[x].j;
              clusters[x].j=newI;
              x++;
              if (clusters[x].i==-1){
                  clusters[x].i=newI;
                  clusters[x].j=tmpJ;
                  ncltrs++;
                  break;
              }
              tmpI=clusters[x].i;
              tmpJ=clusters[x].j;
              clusters[x].i=newI;
              clusters[x].j=newJ;
              newJ=tmpJ;


          }
      if(newJ<clusters[c].i)
          newJ=newJ-clusters[c-1].j+clusters[c].i;
          tmpJ=newJ;
          newI=clusters[c].i;
          newJ=clusters[c].j;
      while(c<ncltrs){
      clusters[c].i=newI;

      newI=newJ;

           }
          newJ  = clusters[c].j;
          clusters[c].i=newJ;

  }
    for (unsigned i=1;i<nPartitions;i++) {
        newI = clusters[c].i + noOfNodesToProcessForEachThread;
        while (clusters[c].j < newI && c < ncltrs) {
            if (clusters[c].i > newI) {
                newI =   newI+newI-clusters[c].j+clusters[c].i;

            //setNewI
            } else {
                newI = newI + clusters[c].i-clusters[c].j+clusters[c].i;
                //setNewI()
            }
            c++;
        }
        if (clusters[c].j<newI) {
            cout << "big Error" << endl;
        return ;
        }
        // posto per ulteriore possibile ottimizzazione
        partitions[i]=newI;
        newJ=clusters[c].j;
            tmpI=clusters[c].i;
            tmpJ=clusters[c].j;
            clusters[c].i=newI;

            clusters[c].j=newJ;
            newI=tmpI;
            newJ=tmpJ;
        }

    }





