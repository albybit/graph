#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Graph.h"
using namespace std;
int main (int argc, char* argv[]) {
    ifstream stat;
    ifstream gra;
    if (argc!=3){
        cout<<"wrong arguments";
        return -1;
    }
stat.open(argv[2]); //.stat
 gra.open(argv[1]);
 if (!gra){
     cout << ".gra file did not open";
     return -1;
 }
 if (!stat){
     cout <<".stat file did not open";
     return -1;
 }
Graph gp(stat,gra);
//.gra

    return 0;
}
