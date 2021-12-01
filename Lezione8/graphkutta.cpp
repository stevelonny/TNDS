#include "differenzia.hpp"
#include "vettoriale.hpp"
#include <iostream>
#include <string>

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"

using namespace std;

int main(int argc, const char** argv){
    if(argc!=2){
        cerr << "Uso del programma " << argv[0] << "<passo>" << endl;
        exit(-1);
    }

    TApplication myApp("myApp", 0, 0);

    Kutta kut;

    OscillatoreArmonicoSemplice osc;
    osc.setOmega(1);
    double tmax{70};
    double h{atof(argv[1])};
    vector<double> x{0., 1.};
    double t{0.};

    TGraph myGraph;
    int nstep{int(tmax/h+0.5)};
    for(int i=0; i<nstep; i++){
        myGraph.SetPoint(i, t, x[0]);
        x = kut.Passo(t,x,h,osc);
        t += h;
    }    
    TCanvas c;
    c.cd();
    string title = "Oscillatore armonico Runge-Kutta, h = ";
    title+=to_string(h);
    myGraph.SetTitle(title.c_str());
    myGraph.GetXaxis()->SetTitle("Tempo t [s]");
    myGraph.GetYaxis()->SetTitle("Posizione x [m]");
    myGraph.Draw("AL");
    myApp.Run();
    
    return 0;
}