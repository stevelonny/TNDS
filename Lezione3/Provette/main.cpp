#include <iostream>
#include <fstream>

#include "stats.hpp"

using namespace std;

int main(int argc, char** argv){

    if(argc<3){
        cerr << "Uso del programma: " << argv[0] << " ndata filename" << endl;
        return -1;
    }

    int ndata = atoi(argv[1]);
    
    const char* filename = argv[2];
    vector<double> data;
    if(ndata==0){
        data = Read<double>(filename);
        ndata = data.size();
    }
    else{
        data = Read<double>(filename, ndata);
    }
    
    cout << "Primi 5 valori:" << endl;
    Print(data, 5, true);
    cout << "Ultimi 5 valori:" << endl;
    Print(data, 5, false);

    cout << "Media: " << Mean<double>(data) << endl;
    cout << "Deviazione standard: " << StdDev<double>(data) << endl;
    cout << "Varianza: " << Variance<double>(data) << endl << endl;
    //cout << "Mediana: " << Median<double>(data) << endl << endl;

    Write("out.txt", data, ndata);

    return 0;
}