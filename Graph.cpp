//
// Created by alby on 11/22/20.
//

#include "Graph.h"

#include <utility>
Barrier barrier(nPartitions);
void Graph::computeClusters() {
    int remaining = numberOfNodesToProcess % nPartitions;
    int tmpI = -1, tmpJ = -1, newI, newJ, c = 0, x = 1;
    for (int i = 0; i < nPartitions && noOfNodesToProcessForEachThread > 0; i++) {
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
    int eavg;
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

    for (int i=0;i<nPartitions;i++){
      modifiednodes[i].array=(struct mn_linked **)(malloc(sizeof(struct mn_linked *) * v));
      modifiednodes[i].last=NULL;
      modifiednodes[i].first=NULL;
      edgesvisited[i]= static_cast<int *>(calloc(v, sizeof(int)));
      nedgesvisited[i]= static_cast<int *>(malloc(sizeof(int)*v));

    }
    nNodes=v;
   edges.reserve(nNodes);
   parents.reserve(nNodes);

    incomingedges.reserve(nNodes);
secondroots.array=(struct rts_linked **)(malloc(sizeof(struct rts_linked* ) * v));
    roots.array=(struct rts_linked **)(malloc(sizeof(struct rts_linked* ) * v));
    leafs.array=(struct lf_linked **)(malloc(sizeof(struct lf_linked* ) * v));
    leafs.last=leafs.first=NULL;

    secondQueue.array=(struct lf_linked **)(malloc(sizeof(struct lf_linked* ) * v));

    secondQueue.last=secondQueue.first=NULL;
    secondroots.last=secondroots.first=NULL;
    roots.last=NULL;
    roots.first=NULL;
    for(int u=0;u<v;u++) {
       InsertRoot(u);
        set<int> c = set<int>();
        edges.emplace_back(c);
        parents.emplace_back(c);
        incomingedges.emplace_back(c);
        InsertLeaf(u);
       // edges.emplace_back(c);
        //edgesVisited.reserve(nPartitions);
    }
    e=e+nNodes;
    cscnode.csc_indices=(int*)malloc(sizeof(int)*(v+1));
    cscnode.csc_nodes=(int*)malloc(sizeof(int)*(e*2));
    for (int i=0;i<e*2;i++){
        cscnode.csc_nodes[i]=-1;
    }
    clusters=(struct nodesAP*)malloc(sizeof(struct nodesAP)*nPartitions);
    for (int i=0;i<nPartitions;i++)
    {
        nOfNodesProcessed[i]=0;   clusters[i].i = -1;
        partitions[i] = 0;
        clusters[i].j=-1;;
    }
    stri.clear();
    nodes= static_cast<Node *>(malloc(sizeof(struct Node) * nNodes));
    lengthOfArrayEdgesVisited=(int *)calloc(nPartitions,sizeof(int));
   for (int i=0;i<nNodes;i++) {

       nodes[i].parent=-1;
       nodes[i].pt.path=(int *) malloc(sizeof(int)*10);
    }
    Barrier barrier(nPartitions);

}
void Graph::assignPath(int index, int node, struct path vector) {
    if (modifiednodes[index].array[node]==NULL){
    modifiednodesEmplace(index,node,0,vector,2);
    }
   modifiednodes[index].array[node]->modifiednode.pt=vector;
    modifiednodes[index].array[node]->node=node;
    if (modifiednodes[index].array[node]->modified==1)
        modifiednodes[index].array[node]->modified=3;
}
void Graph::test(){

    DeleteRoot(9);
   struct path ptnull,pt2;
InitPath(&ptnull);
InitPath(&pt2);
 EmplaceNodeInPath(&ptnull,10);
    EmplaceNodeInPath(&ptnull,12);
    EmplaceNodeInPath(&ptnull,13);
/*


    int f[4]={2,4,0,2};
    auto c=[this,f]() {
     for (int i=0;i<2;i++){
         struct mn_linked *n=modifiednodes[1].array[f[i]];
      // for (struct mn_linked *n = modifiednodes[1].first; n != NULL; n = n->next) {
           if(n->modified==2){
               cout<<"path of node:"<<n->node<<endl;
               for (int i=0; i<=n->modifiednode.pt.lastElementIndex;i++)
                   cout<<n->modifiednode.pt.path[i]<<endl;
               cout<< "endPath"<<endl;
           }
           if(n->modified==1){
               cout<<"parent : "<<n->modifiednode.parent<<" node: "<<n->node <<endl;
           }
           if (n->modified==3){
               cout<<"parent : "<<n->modifiednode.parent<<" node: "<<n->node <<endl;
               cout<<"path"<<endl;
               for (int i=0; i<=n->modifiednode.pt.lastElementIndex;i++)
                   cout<<n->modifiednode.pt.path[i]<<endl;
               cout<< "endPath"<<endl;
           }
       }
   };
    auto d=[this,f](){
    for (int i=0;i<3;i++){
        cout<<"parend of node 2 and then 4\n"<<nodes[f[i]].parent<<endl;

        for (int c=0;c<=nodes[f[i]].pt.lastElementIndex;c++){
            cout<<nodes[f[i]].pt.path[c];
            cout<<endl;
        }
    }
};
    auto p=[this](){

    };
    modifiednodesEmplace(1,4,2,ptnull,1);
    modifiednodesEmplace(2,2,4,ptnull,1);

   // invoke(c);
    modifiednodesEmplace(2,6,4,ptnull,1);
   // modifiednodesEmplace(1,2,0,ptnull,2);
    //invoke(c);
    assignPath(1,2,ptnull);
   updateParent(1,8,2);
   nodes[9].pt=ptnull;

    commitUpdates();
;
/*vector<thread> t;  //test barrier
t.reserve(nPartitions);
for (unsigned i=0;i<nPartitions;i++){
    t.emplace_back(thread([this]{  int d=3;
        while(d>=0){
            d--;
            barrier.Wait();
            cout<<d<<endl;
        }}));

}
for (unsigned i=0;i<nPartitions;i++){
    t[i].join();

}
cout<<nodes[2].parent<<endl<<"aposdj";
*/
   return;
}
void Graph::divideJobWrapper(){

    if (anothercontrolvariable)
    commitUpdates();
    else
        anothercontrolvariable=1;
    divideJob();

}
void Graph::divideJob() {
    int i;

   for (i=0;i<nPartitions;i++) {

       clusters[i].i=0;
       clusters[i].j=0;
    }
    if (numberOfNodesToProcess<0)
    {
        divideJobM.unlock();
        return ;
    }

    int x= numberOfNodesToProcess/nPartitions;
    noOfNodesToProcessForEachThread=x;
    if (controlVariable==0) {

        ncltrs=nPartitions;
        for (i = 0; i < nPartitions && x > 0; i++) {

            clusters[i].i=partitions[i] = i * x;
            clusters[i].j=noOfNodesToProcessForEachThread+clusters[i].i;

            nOfNodesToProcess[i] = x;
        }
        i=numberOfNodesToProcess%nPartitions;

        nOfNodesToProcess[0]+=i;
        clusters[0].j+=i;
        clusters[0].i=0;
        for (int c=1;c<nPartitions;c++)
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
    int i=0;

   Barrier barrier(nPartitions);
    init(stat);
    build(gra);
   // test();
    numberOfNodesToProcess=roots.numberofroots;
   divideJobWrapper();


  vector<thread> t;
    t.reserve(nPartitions);
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i=0;i<nPartitions;i++)
        t.emplace_back( thread( [this, i] { compute_dfs_by_comparing_path(i); }));
    for (int i=0;i<nPartitions;i++)
        t[i].join();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout<<duration<<endl;
   InsertLeafsInArray();
    printIt();
    anothercontrolvariable=0;
    divideJobWrapper();


    for (int i= 0;i<nPartitions;i++){
        for (int c=0;c<lengthOfArrayEdgesVisited[i];c++){
            edgesvisited[i][nedgesvisited[i][c]]=0;
        }
        lengthOfArrayEdgesVisited[i]=0;
    } /*
    vector<thread> th1;
    t.reserve(nPartitions);
     t1 = std::chrono::high_resolution_clock::now();
    for (int i=0;i<nPartitions;i++)
        th1.emplace_back( thread( [this, i] { SubGraphSize(i); }));
    for (int i=0;i<nPartitions;i++)
        th1[i].join();
     t2 = std::chrono::high_resolution_clock::now();
     duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

*/
    printIt();


}
void Graph::printIt() {

    for (int i = 0; i <nNodes; i++) {


        cout << "node: " << i << endl;
        cout << "parent: " << nodes[i].parent << endl;
        cout << "path: " << endl;
        for (int c = 0; c < nodes[i].pt.lastElementIndex; c++)
            cout << nodes[i].pt.path[c] << endl;
        cout << endl;
}


}
void Graph::InsertRoot(int u) {
roots.array[roots.numberofroots]=InsertRootInLinkedList(u);
roots.numberofroots++;
}
void Graph::InsertRootII(int u) {
    secondroots.array[secondroots.numberofroots]=InsertRootInLinkedListII(u);
    secondroots.numberofroots++;
}
void Graph::build(FILE *gra) {
    int u, v;
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
           parents[v].insert(u);
          DeleteRoot(v);
            token=strtok(NULL," ");
        }
    }
    {
        for (int z=0;z<nNodes;z++){
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
void Graph::InsertEdge(int u,int v) {
  edges[u].insert(v);
  incomingedges[v].insert(u);
}

void Graph::DeleteRoot(int i) {
    struct rts_linked *next,*previous,*s;
    s=roots.array[i];
    roots.array[i]=NULL;

   if (s==NULL)
   {
       return;
   }
   next=s->next;
   previous=s->previous;
  free(s);
  if (next==NULL && previous==NULL){
      roots.first=NULL;
      roots.last=NULL;
      return;
  }
  if (next!=NULL && previous==NULL){
     roots.first=next;
     next->previous=NULL;
         roots.last=NULL;
      return;
  }
  if (next==NULL && previous!=NULL){
      roots.last=previous;
      previous->next=NULL;
      return ;
  }
  if (next!=NULL && previous!=NULL){
      previous->next=next;
      next->previous=previous;
      return ;
  }
}
rts_linked *Graph::InsertRootInLinkedList(int u) {
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
int Graph::getPath(struct path *newpath,int threadIndex,int node) {
    if (NULL != modifiednodes[threadIndex].array[node]){
        if (modifiednodes[threadIndex].array[node]->modified!=1) {
           *newpath = modifiednodes[threadIndex].array[node]->modifiednode.pt;
            return 1;
        }
    }
        if (isEmpty(&(nodes[node].pt))){
            return 2;
        }
        else{
            *newpath=nodes[node].pt;

            return 3;
        }


}
void Graph::compute_dfs_by_comparing_path(int threadIndex) {
    int  in1, in2, c = threadIndex;
    int xin1,xin2;
    struct path oldPath,newPathS;
    int node,childnode,ok,ok1=-1;
    while (roots.numberofroots>0) {
        c=threadIndex;
        xin1= clusters[threadIndex].i;// ulteriore ottimizzazione
        xin2=clusters[threadIndex].j;

        while (clusters[c].i<clusters[c].j ) {

            node = roots.array[clusters[c].i]->node;
            ok = getPath(&newPathS,threadIndex, node);

            in1 = cscnode.csc_indices[node]+1 ;
            in2 = cscnode.csc_indices[node+ 1];
            for (int z = in1; z < in2; z++) {      struct path newPath;
                InitPath(&newPath);
           if (ok == 2) {
                   ok1=1;
                    EmplaceNodeInPath(&newPath,node);
                }else{
                    for (int i=0;i<newPathS.lastElementIndex;i++)
                        EmplaceNodeInPath(&newPath,newPathS.path[i]);

                }
           notLeafs[threadIndex].insert(node);

                childnode = cscnode.csc_nodes[z];
                EmplaceNodeInPath(&newPath,childnode);
                ok = getPath(&oldPath, threadIndex, childnode);
                switch (ok) {
                    case 1:
                        if (IsPathLower(&newPath,&oldPath)) {
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
                            (nodes[childnode].pt)=newPath ;
                            nodes[childnode].parent=node;
                        }else {
                            modifiednodesEmplace(threadIndex,childnode,0,newPath,2);
                            updateParent(threadIndex, node, childnode);
                        }
                        countEdge(threadIndex, childnode);
                        break;
                    case 3:
                        if (IsPathLower(&newPath,&oldPath)) {
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
newPath.lastElementIndex--;
            }

/*if (ok1==1) {
    ok1=0;
    newPath.lastElementIndex--;
}*/
            clusters[c].i++;
            nOfNodesToProcess[threadIndex]--;
            nOfNodesProcessed[threadIndex]++;
        }
        synchroni=0;
        barrier.Wait();
        unique_lock<mutex> lck(divideJobM,try_to_lock);
        if (lck.owns_lock())
        {
            synchroni++;
            debug++;
            if (debug==1){

            }
         if (synchroni==1)
            divideJobWrapper();
            lck.unlock();
        }
        barrier.Wait();
    }

}
void Graph::updateParent(int threadIndex,int node,int childnode){
    struct path c;
    c.path=(int *)malloc(sizeof(int)*10);
    if( modifiednodes[threadIndex].array[childnode]==NULL)
    modifiednodesEmplace(threadIndex,node,childnode,c,1);
    else{
        modifiednodes[threadIndex].array[childnode]->node=childnode;
        modifiednodes[threadIndex].array[childnode]->modifiednode.parent=node;
        if (modifiednodes[threadIndex].array[childnode]->modified==2){
            modifiednodes[threadIndex].array[childnode]->modified=3;
        }
    }
}
void Graph::commitUpdates(){
    map<int, int> c;


    roots.first=NULL;
    roots.last=NULL;
    roots.numberofroots=0;
    numberOfroots=roots.numberofroots;
struct path pt;
int ok,ok1=-2;
    for (int i=0;i<nPartitions;i++){
        for (auto &f: notLeafs[i]){
//            leafs.erase(f);
//cout<<f<<"asdd "<<endl;
DeleteLeaf(f);
        }
        for ( struct mn_linked *c=modifiednodes[i].first ; c!=NULL; c=c->next ) {
            ok=getPath(&pt,0,c->node);
            if (ok==3){
            if (IsPathLower(&(c->modifiednode.pt),&pt)) {
                ok1=4;
            }
            }
                switch (c->modified){
                case 1:
                    if(ok==3 && ok1==4)
                    nodes[c->node].parent = c->modifiednode.parent;
                    if(ok!=3)
                        nodes[c->node].parent = c->modifiednode.parent;
                    break;
                case 2:
                        if(ok==3 && ok1==4){
                            nodes[c->node] = c->modifiednode;
                    }
                    if(ok!=3){
                        nodes[c->node] = c->modifiednode;
                    }

                    break;
                case 3:
                        if(ok==3 && ok1==4){
                            nodes[c->node] = c->modifiednode;

                    }
                    if(ok!=3){
                        nodes[c->node] = c->modifiednode;
                    }

                    break;
            }

            ok1=-2;
            free(modifiednodes[i].array[c->node]);
        modifiednodes[i].array[c->node]=NULL;
        }modifiednodes[i].last=modifiednodes[i].first=NULL;
      for (int o=0; o<lengthOfArrayEdgesVisited[i];o++){
          if (c.find(nedgesvisited[i][o])!= c.end())
           {
               c.find(nedgesvisited[i][o])->second+=edgesvisited[i][nedgesvisited[i][o]];


               if (incomingedges[nedgesvisited[i][o]].size()<= c.find(nedgesvisited[i][o])->second){
                   InsertRoot(nedgesvisited[i][o]);

                   nedgesvisited[i][o]=nedgesvisited[i][lengthOfArrayEdgesVisited[i]-1];
                   lengthOfArrayEdgesVisited[i]--;
                  o--;
               }
           }
           else{
               c.emplace(nedgesvisited[i][o],edgesvisited[i][nedgesvisited[i][o]]);
               if (incomingedges[nedgesvisited[i][o]].size()<= c.find(nedgesvisited[i][o])->second){
                   InsertRoot(nedgesvisited[i][o]);
                   nedgesvisited[i][o]=nedgesvisited[i][lengthOfArrayEdgesVisited[i]-1];
                   lengthOfArrayEdgesVisited[i]--;
o--;

               }
           }

      }
        nOfNodesProcessed[i]=0;


    }
    numberOfNodesToProcess=roots.numberofroots;
}



void Graph::modifiednodesEmplace(int index, int node, int child_node,struct path newPath, int modified) {
    struct mn_linked *c, *n;
    int _node;
    c = (struct mn_linked *) (malloc(sizeof(struct mn_linked)));
    switch (modified) {
        case 1://modified parent emplace =1
            c->modifiednode.parent = node;
            c->node = child_node;
            _node = child_node;
            c->modified = 1;
            break;
        case 2://modified vectors emplace modified=2
            (c->modifiednode.pt) = newPath;
            c->node = node;
            _node = node;
            c->modified = 2;
            break;
    }
    if (modifiednodes[index].array[_node] != NULL) {
        if (modifiednodes[index].array[_node]->modified == 3) {
            if (modified == 2) {
            (modifiednodes[index].array[_node]->modifiednode.pt) = newPath;

        } else {
            modifiednodes[index].array[_node]->modifiednode.parent = node;
        }
    } else if (modifiednodes[index].array[_node]->modified != modified) {

        modifiednodes[index].array[_node]->modified = 3;
        if (modifiednodes[index].array[_node]->modified == 1) {
            modifiednodes[index].array[_node]->modifiednode.parent= c->modifiednode.parent ;

        } else {
            modifiednodes[index].array[_node]->modifiednode.pt=c->modifiednode.pt ;
        }

    }
        else if (modifiednodes[index].array[_node]->modified == modified) {
if(            modifiednodes[index].array[_node]->modified==2)
    modifiednodes[index].array[_node]->modifiednode.pt=newPath;
else if(modifiednodes[index].array[_node]->modified==1){
    modifiednodes[index].array[_node]->modifiednode.parent=node;
}
        }

    return;
}
        modifiednodes[index].array[_node]=c;
    if (modifiednodes[index].first==NULL)
    {
        c->next=NULL;
        c->previous=NULL;
        modifiednodes[index].first=c;

        modifiednodes->last=NULL;
        return;
    }
    if (modifiednodes[index].last==NULL){
        c->previous=modifiednodes[index].first;
        modifiednodes[index].first->next=c;
        c->next=NULL;
        modifiednodes[index].last=c;
        return;
    }
    c->previous=modifiednodes[index].first;
    n=modifiednodes[index].first->next;
    modifiednodes[index].first->next=c;
    if (n==NULL) {
        modifiednodes[index].last = c;


        modifiednodes[index].first->next=modifiednodes[index].last;
        return ;
    }
    n->previous=c;
    c->next=n;
}
void Graph::countEdge(int threadIndex, int node) {
    if(edgesvisited[threadIndex][node]==0)
    {
        nedgesvisited[threadIndex][lengthOfArrayEdgesVisited[threadIndex]]=node;

        lengthOfArrayEdgesVisited[threadIndex]++;
    }
    edgesvisited[threadIndex][node]++;

}
void Graph::InsertLeafsInArray(){
    int c=0;
    free(leafs.array);
    leafs.array=(struct lf_linked **)(malloc(sizeof(struct lf_linked* ) *nNodes ));

    for (struct lf_linked *d = leafs.first; d!=NULL; d=d->next){
        //cout<<"lllf"<<d->leaf<<endl;
        leafs.array[c]=d;
        c++;

    }
    leafs.numberofleafs=c;
    numberOfNodesToProcess=c;
}
void Graph::insertRootsInArray() {
    int c=0;
    free(roots.array);
    roots.array=(struct rts_linked **)(malloc(sizeof(struct rts_linked* ) *nNodes ));

    for (struct rts_linked *d = roots.first; d!=NULL; d=d->next){
       roots.array[c]=d;
      InsertRootII(d->node);
      DeleteLeaf(d->node);
        c++;

    }
    roots.numberofroots=c;
    numberOfroots=c;
    numberOfNodesToProcess=c;
}

bool Graph::isEmpty(struct path * pt) {
    if(pt->lastElementIndex==0)
        return true;
    return false;
}

bool Graph::IsPathLower(struct path *pt1, struct path *pt2) {
   int minc;
   minc=min((*pt1).lastElementIndex,(*pt2).lastElementIndex);
    for (int i=0;i<minc;i++){
        if (pt1->path[i]<pt2->path[i])
            return true;
    }
    return false;
}

void Graph::InitPath(struct path *p) {
p->path=(int *)malloc(sizeof(int)*10);
}

void Graph::EmplaceNodeInPath(struct path *pPath, int node) {
int *c;
 if (pPath->lastElementIndex>=pPath->sPath-1){
     c=(int*)malloc(sizeof(int)*pPath->sPath);
     for (int i=0;i<pPath->lastElementIndex;i++)
         c[i]=pPath->path[i];
     free(pPath->path);
     pPath->path=NULL;
     pPath->sPath=pPath->sPath*3;
     pPath->path=(int*)malloc(sizeof(int)*pPath->sPath);
     for (int i=0;i<pPath->lastElementIndex;i++)
         pPath->path[i]=c[i];
     pPath->path[pPath->lastElementIndex]=node;
 }else
pPath->path[pPath->lastElementIndex]= node;

    pPath->lastElementIndex++;
}

void Graph::copyPath(struct path *pt1, struct path *pt2) {
   pt1->path=NULL;
    pt1->path=(int *)malloc(sizeof(int)*pt2->sPath);

//for(int i=0;i< pt2->lastElementIndex;i++)
  // pt1->path[i]=pt2->path[i];
    memcpy(pt1->path, pt2->path, 4*pt2->lastElementIndex);
    pt1->lastElementIndex=pt2->lastElementIndex;
    return;
}

void Graph::SubGraphSize(int threadIndex) {
    int  in1, in2, c = threadIndex;
    int xin1,xin2;
    int node,childnode,ok,ok1=-1,parent;

    while(leafs.numberofleafs>0){
        barrier.Wait();
        c=threadIndex;
        xin1= clusters[threadIndex].i;// ulteriore ottimizzazione
        xin2=clusters[threadIndex].j;
       while(clusters[c].i<clusters[c].j){
           node=leafs.array[clusters[c].i]->leaf;
           for (auto prnt = parents[node].begin(); prnt!=parents[node].end(); prnt++ ) {
               parent=parents[node].extract(prnt).value();
               countEdge(threadIndex, parent);

           }
           clusters[c].i++;
       }

        synchroni=0;
        barrier.Wait();
        unique_lock<mutex> lck(divideJobM,try_to_lock);
        if (lck.owns_lock())
        {
            synchroni++;
            debug++;
            if (debug==1){

            }
            if (synchroni==1) {
                CommitUpdatesII();
                anothercontrolvariable=0;
                numberOfNodesToProcess= leafs.numberofleafs;
                divideJobWrapper();
            } lck.unlock();
        }
        barrier.Wait();

       //only one thread commitUpdates 2
      while(clusters[c].i<clusters[c].j){
          node=leafs.array[clusters[c].i]->leaf;
          nodes[node].subTreeSize++;
   for (auto &child : edges[node]){
       nodes[node].subTreeSize+=nodes[child].subTreeSize+1;
   }

          //compute a prefix sum onCp, obtan
      }
      //compute a prefix sum on Cp obtaining cp

    }
}
void Graph::CommitUpdatesII(){
    leafs.first=leafs.last=NULL;
    leafs.numberofleafs=0;
    leafs.array=NULL;
    map<int,int> c;
for (int i=0;i<nPartitions;i++){
    for (int o=0; o<lengthOfArrayEdgesVisited[i];o++){
        if (c.find(nedgesvisited[i][o])!= c.end())
        {
            c.find(nedgesvisited[i][o])->second+=edgesvisited[i][nedgesvisited[i][o]];


            if (edges[nedgesvisited[i][o]].size()<= c.find(nedgesvisited[i][o])->second){
                InsertLeaf(nedgesvisited[i][o]);

                nedgesvisited[i][o]=nedgesvisited[i][lengthOfArrayEdgesVisited[i]-1];
                lengthOfArrayEdgesVisited[i]--;
                o--;
            }
        }
        else{
            c.emplace(nedgesvisited[i][o],edgesvisited[i][nedgesvisited[i][o]]);
            if (edges[nedgesvisited[i][o]].size()<= c.find(nedgesvisited[i][o])->second){
                InsertLeaf(nedgesvisited[i][o]);
                nedgesvisited[i][o]=nedgesvisited[i][lengthOfArrayEdgesVisited[i]-1];
                lengthOfArrayEdgesVisited[i]--;
                o--;

            }
        }

    }
}
}
void Graph::InsertLeaf(int u) {
    leafs.array[leafs.numberofleafs]=InsertLeafInlinkedList(u);
    leafs.numberofleafs++;
}

struct lf_linked *Graph::InsertLeafInlinkedList(int u) {

    if (leafs.first==NULL){
        leafs.first= (struct lf_linked *)(malloc(sizeof(struct lf_linked *)));
        leafs.first->previous=NULL;
        leafs.first->next=NULL;
        leafs.first->leaf=u;
        leafs.last=leafs.first;
        return leafs.first;
    }
    struct lf_linked *l;
    l=leafs.last;
    l->next= (struct lf_linked *)(malloc(sizeof(struct lf_linked*)));
    l=l->next;
    l->previous=leafs.last;
    l->leaf=u;
    l->next=NULL;
    leafs.last=l;
    return l;
}

void Graph::DeleteLeaf(const int &i) {
    struct lf_linked *next,*previous,*s;
    s=leafs.array[i];
    leafs.array[i]=NULL;
    if (s==NULL)
    {
        return;
    }
    next=s->next;
    previous=s->previous;
    free(s);
    if (next==NULL && previous==NULL){
        leafs.first=NULL;
        leafs.last=NULL;
        return;
    }
    if (next!=NULL && previous==NULL){
        leafs.first=next;
        next->previous=NULL;
        leafs.last=NULL;
        return;
    }
    if (next==NULL && previous!=NULL){
        leafs.last=previous;
        previous->next=NULL;
        return ;
    }
    if (next!=NULL && previous!=NULL){
        previous->next=next;
        next->previous=previous;
        return ;
    }
}

struct rts_linked *Graph::InsertRootInLinkedListII(int u) {
    if (secondroots.first==NULL){
        secondroots.first= (struct rts_linked *)(malloc(sizeof(struct rts_linked *)));
        secondroots.first->previous=NULL;
        secondroots.first->next=NULL;
        secondroots.first->node=u;
        secondroots.last=secondroots.first;
        return secondroots.first;
    }
    struct rts_linked *l;
    l=secondroots.last;
    l->next= (struct rts_linked *)(malloc(sizeof(struct rts_linked*)));
    l=l->next;
    l->previous=secondroots.last;
    l->node=u;
    l->next=NULL;
    secondroots.last=l;
    return l;
}



