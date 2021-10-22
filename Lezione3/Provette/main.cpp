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
    Print(data, 5);
    //const char* ffive = "ffive.txt";
    //cout << "Scriviamo primi 5 valori su " << ffive << endl;
    //Print(data, ffive, 5);
    
    cout << "Ultimi 5 valori:" << endl;
    Print(data, -5);
    // const char* lfive = "lfive.txt";
    // cout << "Scriviamo gli ultimi 5 valori su " << lfive << endl;
    // Print(data, lfive, -5);
    
    // cout << "Ordiniamo il vettore" << endl;
    // sort(data.begin(), data.end());
    
    // cout << "Scriviamo tutto il vettore dall'inizio" << endl;
    // const char* fall = "fall.txt";
    // Print(data, fall);
    // cout << "Scriviamo tutto il vettore dal fondo" << endl;
    // const char* lall = "lall.txt";
    // Print(data, lall, false);

    return 0;
}