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
 edgesVisited.reserve(nPartitions);
 modifiedVectors.reserve(nPartitions
         );
for (unsigned i=0;i<nPartitions;i++){
    map<unsigned,unsigned> e;
    map<unsigned,vector<unsigned>> v;
    edgesVisited.push_back(e);
    modifiedVectors.push_back(v);
}

    nNodes=v;
roots.reserve(v);
edges.reserve(nNodes);
edgesVisited.reserve(nNodes);
 for(unsigned u=0;u<v;u++) {
     roots.insert(u);
edges[u]=set<int>();
nodes[u].path;

edgesVisited.reserve(nPartitions);
 }
    e=e+nNodes;
    cscnode.csc_indices=(unsigned*)malloc(sizeof(unsigned)*(v+1));
    cscnode.csc_nodes=(unsigned*)malloc(sizeof(unsigned)*(e));
for (unsigned i=0;i<e;i++){
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

Graph::Graph(FILE *stat, FILE *gra){
    unsigned i=0;
    init(stat);
    build(gra);
    numberOfNodesToProcess=roots.size();
    divideJobWrapper();
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
   for (unsigned i=0;i<nPartitions;i++)
        t.push_back( thread([this,i]{compute_dfs_by_comparing_path(i); }));
for (unsigned i=0;i<nPartitions;i++)
    t[i].join();

    printIt();
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
           for (auto it= edges[z].cbegin();it!=edges[z].cend();it++){
               cscnode.csc_nodes[cscnode.i] = *it;
               cscnode.i++;
           }
            cscnode.csc_indices[cscnode.c]=cscnode.i;
        }
    }

    {
        unsigned i=roots.size()-1;
        for (auto &elem: roots) {
            nextRoots.push_back(elem);
            i--;

        }
    }
    vector<Node> to_swap(nNodes);
    nodes.swap(to_swap);

}

 void Graph::compute_dfs_by_comparing_path(int threadIndex) {
   unsigned i,indexNode_csc,c=0,newPathNode;
     i=partitions[threadIndex];
   map<unsigned,vector<unsigned>> mapp; //mapp just to declare iterator
   auto it_root=mapp.begin();
     while(rootsVector.size()>0){

         while(clusters[c].j<i)
             c++;
         mu[threadIndex].lock();
             modifiedVectors[threadIndex].clear();
         while(nOfNodesToProcess[threadIndex]>0) {
        vector<unsigned>rootsPath;  // root's Path
         indexNode_csc = cscnode.csc_indices[rootsVector[i]];
       if(nodes[rootsVector[i]].path.empty()){
           rootsPath.emplace_back(rootsVector[i]);
            nodes[rootsVector[i]].path=rootsPath;
       }
       rootsPath=nodes[rootsVector[i]].path;



         for (indexNode_csc = +1; indexNode_csc < cscnode.csc_indices[rootsVector[i] + 1]; indexNode_csc++) {
           vector<unsigned> newPathVector,oldPathVector;
            newPathNode=cscnode.csc_nodes[indexNode_csc];
           if (nodes[newPathNode].path.empty()){
               newPathVector=rootsPath;
               newPathVector.emplace_back(indexNode_csc);
               modifiedVectors[threadIndex].emplace(newPathNode,newPathVector);
               newPathVector.pop_back();

           }else {

               newPathVector=rootsPath;
               newPathVector.emplace_back(newPathNode);
                oldPathVector=nodes[newPathNode].path;
               if (oldPathVector != newPathVector) {
                   if (newPathVector<oldPathVector) {
                        modifiedVectors[threadIndex].emplace(newPathNode,newPathVector);
                        newPathVector.pop_back();

                   }

               }
           }
            if (edgesVisited[threadIndex].find(newPathNode)==edgesVisited[threadIndex].end()){
               edgesVisited[threadIndex].emplace(newPathNode,0);
           }

           auto it= edgesVisited[threadIndex].find(newPathNode);
             (it->second)++;

             //fine for più esterno algoritmo 4
         i++;
         if (clusters[c].j > i) {
             clusters[c].i++;
         } else {
             c++;
             i = i - clusters[c - 1].j + clusters[c].i;
             clusters[c].i++;
         }
         }
         nOfNodesToProcess[threadIndex]--;
         nOfNodesProcessed[threadIndex]++;
     }

     mu[threadIndex].unlock();
     divideJobWrapper();
 }
}
void Graph::divideJobWrapper(){
    if (divideJobM.try_lock()) {
        for (unsigned i=0;i<nPartitions;i++)
            mu[i].lock();
        controlVariable = 0;


        numberOfNodesToProcess = nextRoots.size();


        rootsVector.clear();
        for (auto &rele : nextRoots)
            rootsVector.push_back(rele);
        nextRoots.clear();

        for (unsigned i=0;i<nPartitions;i++) {
            for(std::map<unsigned,unsigned>::iterator it = edgesVisited[i].begin(); it != edgesVisited[i].end(); ++it) {
                nodes[it->first].inc_visited_count+=(it->second);
                if (nodes[it->first].inc_visited_count==edges[it->first].size())
                    nextRoots.emplace_back(it->first);
                nodes[it->first].inc_visited_count=0;

            }
            for (auto it = modifiedVectors[i].begin(); it != modifiedVectors[i].cend(); it++) {
         if (nodes[it->first].path.empty())
             nodes[it->first].path=it->second;
                if ((it->second) > nodes[it->first].path) {
                    nodes[it->first].path.clear();
                    nodes[it->first].path = (it->second);
                //    nodes[it->first].parent=nodes[it->first].path(nodes[it->first].)
                }
            }
        }

        divideJob();
        for (unsigned i=0;i<nPartitions;i++)
            mu[i].unlock();
        divideJobM.unlock();
    }
    divideJobM.lock();
    divideJobM.unlock();
}
void Graph::divideJob() {
    unsigned i;

for (i=0;i<nPartitions;i++) { // #TODO costruisci un ciclo esterno che cicla su quello interno attraverso cosi fai try lock
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
    }
i=numberOfNodesToProcess%nPartitions;
    nOfNodesToProcess[i]+=i;
    clusters[0].j+=i;
    partitions[1]+=i;
    for (unsigned c=1;c<nPartitions;c++)
    {
        clusters[c].i+=i;
        clusters[c].j+=i;
    }
}else{
    computeClusters();
}
}

void Graph::printIt() {
    for (unsigned z=0;z<nNodes;z++)
    {  cout<<z<<" ";
        auto it = edges[z].cbegin();
        for (it;it!=edges[z].cend();it++)
            cout<<*it<<" ";
        cout<<endl;
    }
    for (unsigned z=0;z<nNodes;z++){
        cout <<z <<" indice "<< cscnode.csc_indices[z]<<" "<<endl;
        for (unsigned f=cscnode.csc_indices[z];f<cscnode.csc_indices[z+1];f++)
            cout<<cscnode.csc_nodes[f]<<" ";
    cout<<endl;
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




