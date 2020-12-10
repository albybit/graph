//
// Created by alby on 11/22/20.
//

#include "Graph.h"

#include <utility>
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

    for (unsigned i=0;i<nPartitions;i++){
      modifiedparents[i].array=(struct mp_linked **)(malloc(sizeof(struct mp_linked *) * v));
      modifiedparents[i].first=NULL;
      modifiedparents[i].last=NULL;
      edgesvisited[i]= static_cast<int *>(calloc(v, sizeof(int)));
      nedgesvisited[i]= static_cast<int *>(malloc(sizeof(int)*v));

      lengthOfArrayEdgesVisited[i]=0;
      modifiedVectors[i].array=(struct mv_linked **)(malloc(sizeof(struct mv_linked *) * v));
      modifiedVectors[i].first=NULL;
      modifiedVectors[i].last=NULL;
    }
    nNodes=v;
   edges.reserve(nNodes);
    roots.array=(struct rts_linked **)(malloc(sizeof(struct rts_linked* ) * v));
    roots.last=NULL;
    roots.first=NULL;
    for(unsigned u=0;u<v;u++) {
       InsertRoot(u);

        set<int> c = set<int>();
        edges.emplace_back(c);
       // edges.emplace_back(c);
        //edgesVisited.reserve(nPartitions);
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
    nodes= static_cast<Node *>(malloc(sizeof(struct Node) * nNodes));

    clusters=(struct nodesAP*)malloc(sizeof(struct nodesAP)*nNodes);
    for (unsigned i=0;i<nNodes;i++) {
        clusters[i].i = -1;
        clusters[i].j=-1;
        nodes[i].parent=-1;
        nodes[i].pt= static_cast<path *>(malloc(sizeof(struct path )));
        initPath(nodes[i].pt);
    }
    for (unsigned i=0;i<nPartitions;i++) {
        partitions[i] = 0;
    }

}
void Graph::assignPath(int index, unsigned int childnode, struct path* vector) {
    if (modifiedVectors[index].array[childnode]==NULL){
     modifiedVectors[index].array[childnode]= (struct mv_linked *)(malloc(sizeof(struct mv_linked )));
    }
    modifiedVectors[index].array[childnode]->newPath=vector;
}
void Graph::test(){
    return;
}void Graph::divideJobWrapper(){
    if (!divideJobM.try_lock())
    {
        divideJobM.lock();
        divideJobM.unlock();
        return;
    }
    for (unsigned i=0;i<nPartitions;i++)
        mu[i].lock();
    if (anothercontrolvariable)
    commitUpdates();
    else
        anothercontrolvariable=1;
    divideJob();
    for (unsigned i=0;i<nPartitions;i++)
        mu[i].unlock();
    divideJobM.unlock();
}
void Graph::divideJob() {
    unsigned i;

    for (i=0;i<nPartitions;i++) {
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

            nOfNodesToProcess[i] = x;
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

Graph::Graph(FILE *stat, FILE *gra){
    unsigned i=0;
    init(stat);
    build(gra);
    numberOfNodesToProcess=numberOfroots;
   divideJobWrapper();
    printIt();
    test();
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


void Graph::InsertRoot(unsigned int u) {
roots.array[roots.numberofroots]=InsertRootInLinkedList(u);
roots.numberofroots++;
}

void Graph::build(FILE *gra) {
    unsigned u, v;
    char *token;
    char str[2000];
    if (gra!=NULL)
        fgets(str,2000,gra);
    while (fgets(str,2000,gra)!=NULL){
        token = strtok(str, ":");
        if(token==NULL)
            break;

        sscanf(token, "%d", &u);


        token = strtok(NULL, ":");
        sscanf(token,"%[^#]s",str);
        token = strtok(str, " ");
        //  walk through other tokens
        while (token!=NULL) {
            sscanf(token, "%d", &v);
           InsertEdge(u,v);
          DeleteRoot(v);
            token=strtok(NULL," ");
        }
    }
    {
        for (unsigned z=0;z<nNodes;z++){
            cscnode.csc_nodes[cscnode.i]=z;
            cscnode.csc_indices[cscnode.c]=cscnode.i;
            cscnode.c++;
            cscnode.i++;

            for (set<int>::iterator it= edges[z].cbegin();!edges[z].empty()&& it!=edges[z].cend() ;it++){

                cscnode.csc_nodes[cscnode.i] = *it;
                cscnode.i++;
            }
            cscnode.csc_indices[cscnode.c]=cscnode.i;
        }
        cscnode.csc_nodes[cscnode.i]=nNodes;
        cscnode.csc_indices[cscnode.c]=cscnode.i;

    }
    insertRootsInArray();
}
void Graph::InsertEdge(unsigned int u,unsigned int v) {
  edges[u].insert(v);
  edges[v].insert(u);
}

void Graph::DeleteRoot(unsigned int i) {
    struct rts_linked *next,*previous,*s;
    s=roots.array[i];
   if (s==NULL)
   {
       return;
   }
   next=s->next;
   previous=s->previous;
   if (i==0)
   {
       if (next==NULL)
       {
           roots.array[i]=NULL;
           roots.first=NULL;
           roots.last=NULL;
           free(s);
           return;
       }
       next->previous=NULL;
       roots.first=next;
       roots.last=roots.first;
       roots.array[i]=NULL;
       free(s);
       return;
   }
    if (next==NULL){
        if(previous!=NULL)
        previous->next=NULL;
            roots.last=previous;

        roots.array[i]=NULL;
        free(s);
        return;
    }
    if (previous==NULL){
cout<<"big error";
        roots.first=next;
        roots.array[i]=NULL;
        free(s);
        return ;

    }

   previous->next=next;
    next->previous=previous;
 //   free(s);
    return;






}
void Graph::printIt() {
   /* for (unsigned v=0; v<nNodes;cout<<v<<"thisis V"<<endl,v++)
for (unsigned i=cscnode.csc_indices[v]; i<cscnode.csc_indices[v+1];i++)
*/

}
rts_linked *Graph::InsertRootInLinkedList(unsigned int u) {
    if (roots.first==NULL){
        roots.first= (struct rts_linked *)(malloc(sizeof(struct rts_linked *)));
        roots.first->previous=NULL;
        roots.first->next=NULL;
        roots.first->node=u;
        roots.last=roots.first;
        return roots.first;
    }
    struct rts_linked *l;
    l=roots.last;
    l->next= (struct rts_linked *)(malloc(sizeof(struct rts_linked*)));
    l=l->next;
    l->previous=roots.last;
    l->node=u;
    l->next=NULL;
    roots.last=l;
    return l;
}
int Graph::getPath(struct path *newpath,unsigned threadIndex,unsigned node) {
    if (NULL != modifiedVectors[threadIndex].array[node]){
        newpath=modifiedVectors[threadIndex].array[node]->newPath;
        return 1;
    }else{
        if (nodes[node].pt->lastElementIndex==-1)
            return 2;

        else{
            newpath=nodes[node].pt;

            return 3;
        }
    }

}
void Graph::compute_dfs_by_comparing_path(int threadIndex) {
    unsigned i, in1, in2, c = threadIndex, node, ok, childnode,ok1=-1;
    unsigned xin1,xin2;
    xin1= (nNodes/nPartitions)*threadIndex;
    xin2=(nNodes/nPartitions)*(threadIndex+1);

    i = 0;
  struct  rts_linked *rts;
    rts=roots.first;
    while (rts!=NULL) {




        mu[threadIndex].lock();
        while (nOfNodesToProcess[threadIndex] > 0) {
            while (clusters[c].i >= clusters[c].j)c++;
            struct path *oldPath,*newPath;
            node = roots.array[clusters[c].i]->node;
            initPath(oldPath);

            in1 = cscnode.csc_indices[roots.array[clusters[c].i]->node] + 1;
            in2 = cscnode.csc_indices[roots.array[clusters[c].i]->node+ 1];

           ok = getPath(newPath,threadIndex, node);
            if (ok == 2) {
                ok1=1;
                newPath=(struct path*)malloc(sizeof(struct path));
                initPath(newPath);
                emplacenodeinpath(node,newPath);
              modifiedVectorsEmplace(threadIndex,node,newPath);
            }
            for (unsigned z = in1; z < in2; z++) {
                childnode = cscnode.csc_nodes[z];
                emplacenodeinpath(childnode,newPath);
                ok = getPath(oldPath, threadIndex, childnode);

                switch (ok) {
                    case 1:
                        if (isOldBigger(oldPath,newPath)) {
                            if (childnode >= xin1 && childnode < xin2) {
                                nodes[childnode].parent=node;
                                nodes[childnode].pt=newPath;
                            } else
                            {
                                assignPath(threadIndex, childnode, newPath);
                            updateParent(threadIndex, node, childnode);
                        }countEdge(threadIndex, childnode);
                        }
                        break;
                    case 2:
                        if (childnode >= xin1 && childnode < xin2) {
                            nodes[childnode].pt=newPath;
                            nodes[childnode].parent=node;
                        }else {
                            modifiedVectorsEmplace(threadIndex, childnode, newPath);
                            updateParent(threadIndex, node, childnode);
                        }
                        countEdge(threadIndex, childnode);
                        break;
                    case 3:
                        if (isOldBigger(oldPath,newPath)) {
                            if (childnode >= xin1 && childnode < xin2) {
                                nodes[childnode].parent=node;
                                nodes[childnode].pt=newPath;
                            } else
                            {
                                assignPath(threadIndex, childnode, newPath);
                                updateParent(threadIndex, node, childnode);
                            }countEdge(threadIndex, childnode);
                        }

                        break;

                }
                popBackFromPath(newPath);

            }
if (ok1==1) {
    ok1=0;
    popBackFromPath(newPath);
}
            i++;
            clusters[c].i++;
            nOfNodesToProcess[threadIndex]--;
            nOfNodesProcessed[threadIndex]++;
            rts=rts->next;
        }
        mu[threadIndex].unlock();
        divideJobWrapper();
        divideJobM.lock();
        divideJobM.unlock();
        rts=roots.first;
    }
}
void Graph::updateParent(unsigned threadIndex,unsigned node,unsigned childnode){
    if( modifiedparents[threadIndex].array[childnode]==NULL)
      modifiedParentsEmplace(threadIndex,node,childnode);
    else{
        modifiedparents[threadIndex].array[childnode]->node=childnode;

        modifiedparents[threadIndex].array[childnode]->newParent=node;
    }
}
void Graph::commitUpdates(){
    controlVariable=0;
    map<unsigned, unsigned> c;
    struct rts newroots;
    newroots.array=(struct rts_linked **)(malloc(sizeof(struct rts_linked* ) *nNodes ));

    newroots.last=NULL;
    newroots.first=NULL;
    roots=newroots;
    for (unsigned i=0;i<nPartitions;i++){
        for ( struct mp_linked *c=modifiedparents[i].first ; c!=NULL; c=c->next ) {
            nodes[c->node].parent = c->newParent;
//      free(c);      free(modifiedparents[i].array[c->node]);
        modifiedparents[i].array[c->node]=NULL;

        }modifiedparents[i].last=modifiedparents[i].first=NULL;

      for(struct mv_linked *c=modifiedVectors[i].first;c!=NULL;c=c->next) {
          nodes[c->node].pt=c->newPath;
//        no free to spare time
          modifiedVectors[i].array[c->node]=NULL;
      }
      for (unsigned o=0; o<lengthOfArrayEdgesVisited[i];o++){
           if (c.find(nedgesvisited[i][o])!= c.end())
           {
               c.find(nedgesvisited[i][o])->second+=edgesvisited[i][nedgesvisited[i][o]];


               if (edges[nedgesvisited[i][o]].size()<= c.find(nedgesvisited[i][o])->second){
                   InsertRoot(nedgesvisited[i][o]);
                   edgesvisited[i][nedgesvisited[i][o]]=0;
                   c.find(nedgesvisited[i][o])->second=0;
                   nedgesvisited[i][o]=-1;


               }
           }
           else{
               c.emplace(nedgesvisited[i][o],edgesvisited[i][nedgesvisited[i][o]]);
               if (edges[nedgesvisited[i][o]].size()<= c.find(nedgesvisited[i][o])->second){
                   InsertRoot(nedgesvisited[i][o]);
                   edgesvisited[i][nedgesvisited[i][o]]=0;
                   c.find(nedgesvisited[i][o])->second=0;
                   nedgesvisited[i][o]=-1;


               }
           }
      }
      modifiedVectors[i].first=NULL;
        modifiedVectors[i].last=NULL;
        nOfNodesProcessed[i]=0;
        lengthOfArrayEdgesVisited[i]=0;
        lengthOfArrayEdgesVisited[i]=0;
        numberOfNodesToProcess=roots.numberofroots;

    }
}

void Graph::modifiedVectorsEmplace(int index, unsigned int node, struct path *newPath) {
    struct mv_linked * c,*n;
    c=(struct mv_linked *)(malloc(sizeof(struct mv_linked )));
    c->newPath=newPath;
    c->node=node;
    if (modifiedVectors[index].array[node]!=NULL){}else
    modifiedVectors[index].array[node]=c;
    if (modifiedVectors[index].first==NULL)
{
   c->next=NULL;
   c->previous=NULL;
    modifiedVectors[index].first=c;

    modifiedVectors[index].last=NULL;
    return;
}
    if (modifiedVectors[index].last==NULL){
       c->previous=modifiedVectors[index].first;
      modifiedVectors[index].first->next=c;
       c->next=NULL;
        modifiedVectors[index].last=c;
       return;
    }
    c->previous=modifiedVectors[index].first;
    n=modifiedVectors[index].first->next;
    modifiedVectors[index].first->next=c;
    if (n==NULL) {
        modifiedVectors[index].last = c;


    modifiedVectors[index].first->next=modifiedVectors[index].last;
        return ;
    }
    n->previous=c;
    c->next=n;
}

void Graph::modifiedParentsEmplace(unsigned int index, unsigned int node, unsigned int child_node) {
    struct mp_linked * c,*n;
    c=(struct mp_linked *)(malloc(sizeof(struct mp_linked *)));
    c->newParent=node;
    c->node=child_node;

    if (modifiedparents[index].array[child_node]!=NULL){

    }else
        modifiedparents[index].array[child_node]=c;
    if (modifiedparents[index].first==NULL)
    {
        c->next=NULL;
        c->previous=NULL;
        modifiedparents[index].first=c;

        modifiedparents->last=NULL;
        return;
    }
    if (modifiedparents[index].last==NULL){
        c->previous=modifiedparents[index].first;
        modifiedparents[index].first->next=c;
        c->next=NULL;
        modifiedparents[index].last=c;
        return;
    }
    c->previous=modifiedparents[index].first;
    n=modifiedparents[index].first->next;
    modifiedparents[index].first->next=c;
    if (n==NULL) {
        modifiedparents[index].last = c;


        modifiedparents[index].first->next=modifiedparents[index].last;
        return ;
    }
    n->previous=c;
    c->next=n;
}

void Graph::countEdge(unsigned int threadIndex, unsigned int node) {
    if(edgesvisited[threadIndex][node]==0)
    {
        nedgesvisited[threadIndex][lengthOfArrayEdgesVisited[threadIndex]]=node;
        lengthOfArrayEdgesVisited[threadIndex]++;
    }
    edgesvisited[threadIndex][node]++;

}

void Graph::insertRootsInArray() {
    unsigned c=0;
    free(roots.array);
    roots.array=(struct rts_linked **)(malloc(sizeof(struct rts_linked* ) *nNodes ));

    for (struct rts_linked *d = roots.first; d!=NULL; d=d->next){
       roots.array[c]=d;

        c++;

    }
    roots.numberofroots=c;
    numberOfroots=c;
    numberOfNodesToProcess=c;
}

void Graph::emplacenodeinpath(int node, struct path *pt) {
    if (pt->lastElementIndex+1> pt->sPath)
    {
        int newSize=(pt->sPath*3);
        struct path *aBiggerPathIsNeeded;
        aBiggerPathIsNeeded=(struct path*)malloc(sizeof(struct path));
        aBiggerPathIsNeeded->path= (int *) malloc(sizeof(int) * newSize);
        aBiggerPathIsNeeded->sPath=newSize;
        aBiggerPathIsNeeded->lastElementIndex=pt->lastElementIndex;
        for (unsigned i=0;i<=pt->lastElementIndex;i++)
           aBiggerPathIsNeeded->path[i]= pt->path[i];
     //   free(pt);

        pt=aBiggerPathIsNeeded;
    }
    pt->lastElementIndex++;
    pt->path[pt->lastElementIndex]=node;
    return;
}



void Graph::initPath(struct path *pt){
if(pt==NULL)
    pt=(struct path*)malloc(sizeof(struct path));
    pt->path= (int*)(malloc(sizeof(int) * 10));
    pt->sPath=10;
    pt->lastElementIndex=-1;

}
int Graph::isOldBigger(struct path *opt, struct path *npt){
    int x;
    x=min(opt->lastElementIndex,npt->lastElementIndex);
    if (opt->lastElementIndex==-1)
        return 1;
    for (unsigned i=0;i<=x;i++)
        if (opt->path[i]>npt->path[i])
            return 1;
        return 0;
}

void Graph::popBackFromPath(struct path *pt) {

    pt->lastElementIndex--;

}
