//
// Created by aberto on 24/09/20.
//

#include "Graph.h"
#include "Path.h"


void Path::init(int n) {
    unsigned z;
    for (unsigned x=0;x<nPartitions-2;x++) {


        this->pathTail[x]= static_cast<int *>(malloc(sizeof(int) * n));
        for (z=0;z<n;z++)
            this->pathTail[x][z]=-1;

    }

    this->reserved[0] = static_cast<int *>(malloc(sizeof(int) * n));
    this->reserved[1]=static_cast<int*> (malloc(sizeof(int)*n));
  for (z=0;z<n;z++) {
      this->reserved[0][z] = 0;
    this->reserved[1][z]=-1;
  }
}

bool Path::operator<(const Path &p) {
return false;
}

void Path::add(const unsigned int u, const unsigned int v) {

}

Path& Path::operator=(const Path &newPath){
    if (this!= &newPath) {
        unsigned z;
        for (unsigned x=0;x<nPartitions-2;x++) {


            for (z=0;z<n;z++)
                this->pathTail[x][z]=newPath.pathTail[x][z];

        }

        for (z=0;z<n;z++) {
            this->reserved[0][z] = newPath.reserved[0][z];
            this->reserved[1][z]=newPath.reserved[1][z];
        }


    }
return *this;
}
void Path::print(){

}