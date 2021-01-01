#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Graph.h"
using namespace std;
int main (int argc, char* argv[]) {
    FILE *stat;
    FILE *gra;
    if (argc!=3){
        cout<<"wrong arguments";
        return -1;
    }
    stat=fopen(argv[2],"r");
    gra=fopen(argv[1],"r");
    if (gra==NULL){
        cout << ".gra file did not open";
        return -1;
    }
    if (stat==NULL){
        cout <<".stat file did not open";
        return -1;
    }
    Graph gp(stat,gra);

    return 0;
}