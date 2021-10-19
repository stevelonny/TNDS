#include <iostream>
#include <fstream>
//root
#include "TH1F.h"

//mia libreria
#include "stats.hpp"

using namespace std;

int main(int argc, char** argv){

    if(argc<3){
        cerr << "Uso del programma: " << argv[0] << " ndata filename" << endl;
        return -1;
    }

    int ndata = atoi(argv[1]);
    
    const char* filename = argv[2];

    vector<double> data = Read<double>(filename, ndata);

    return 0;
}