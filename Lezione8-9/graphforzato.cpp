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
    if(argc!=6){
        cerr << "Uso del programma " << argv[0] << " <passo> <omega0> <omega> <alpha^-1> <tmax>" << endl;
        exit(-1);
    }

    TApplication myApp("myApp", 0, 0);

    Kutta kut;

    OscillatoreArmonicoForzato osc;
    osc.setOmega0(atof(argv[2]));
    osc.setOmega(atof(argv[3]));
    osc.setAlpha(1./(atof(argv[4])));
    double tmax{atof(argv[5])};
    double h{atof(argv[1])};
    vector<double> x{0., 0.};
    double t{0.};

    TGraph myGraph;
    int nstep{int(tmax/h+0.5)};
    for(int i=0; i<nstep; i++){
        myGraph.SetPoint(i, t, x[0]);
        x = kut.Passo(t,x,h,osc);
        t += h;
    }
    cout << "Posizione finale: " << x[0] << endl << "Velocità finale: " << x[1] << endl;
    TCanvas c;
    c.cd();
    string title = "Oscillatore armonico forzato Kutta, h = ";
    title+=to_string(h);
    myGraph.SetTitle(title.c_str());
    myGraph.GetXaxis()->SetTitle("Tempo t [s]");
    myGraph.GetYaxis()->SetTitle("Posizione x [m]");
    myGraph.Draw("AL");
    myApp.Run();
    
    return 0;
}