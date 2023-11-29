#include <iostream>
#include <fstream>
//root
#include "TH1F.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TCanvas.h"
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

    TApplication app("app", 0, 0);

    vector<double> data = Read<double>(filename, ndata);

    TH1F histo("histo", "histo", 100, -10, 100);
    histo.StatOverflows(kTRUE);
    for(int i=0; i<data.size(); i++){
        histo.Fill(data[i]);
    }

    cout << "Media dei valori caricati: " << histo.GetMean() << endl;

    TCanvas mycanvas("Histo", "Histo");
    histo.Draw();
    histo.GetXaxis()->SetTitle("measurement");

    app.Run();
    
}