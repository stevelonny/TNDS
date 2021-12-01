#include "differenzia.hpp"
#include "vettoriale.hpp"
#include <iostream>
#include <string>

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TLegend.h"

using namespace std;

int main(int argc, const char** argv){
    if(argc!=2){
        cerr << "Uso del programma " << argv[0] << " <tmax>" << endl;
        exit(-1);
    }

    double tmax{atof(argv[1])};

    TApplication myApp("myApp", 0, 0);

    TF1 *fsen{new TF1("Sen(x)", "sin(x)", 0, tmax)};
    TGraph *senx{new TGraph(fsen)};
    TGraph *eul01   {new TGraph()};
    TGraph *eul001  {new TGraph()};
    TGraph *eul0001 {new TGraph()};

    Eulero eul;
    OscillatoreArmonicoSemplice osc(1.);

    vector<double> x{0., 1.};
    
    double t{0.};
    double h{0.1};
    int nstep{int(tmax/h+0.5)};
    for(int i{0}; i<nstep; i++){
        eul01->SetPoint(i, t, x[0]);
        x = eul.Passo(t, x, h, osc);
        t += h;
    }
    t = 0.;
    x = {0., 1.};
    h = 0.01;
    nstep = int(tmax/h+0.5);
    for(int i{0}; i<nstep; i++){
        eul001->SetPoint(i, t, x[0]);
        x = eul.Passo(t, x, h, osc);
        t += h;
    }
    t = 0.;
    x = {0., 1.};
    h = 0.001;
    nstep = int(tmax/h+0.5);
    for(int i{0}; i<nstep; i++){
        eul0001->SetPoint(i, t, x[0]);
        x = eul.Passo(t, x, h, osc);
        t += h;
    }

    eul01   ->SetLineColor(kBlue);
    eul001  ->SetLineColor(kGreen);
    eul0001 ->SetLineColor(kYellow);

    TMultiGraph *mgr{new TMultiGraph()};

    TCanvas *c{new TCanvas()};
    c->cd();

    eul01   ->SetLineColor(kBlue);
    eul001  ->SetLineColor(kGreen);
    eul0001 ->SetLineColor(kYellow);
    
    mgr->Add(senx);
    mgr->Add(eul01);
    mgr->Add(eul001);
    mgr->Add(eul0001);

    eul01   ->SetLineColor(kBlue);
    eul001  ->SetLineColor(kGreen);
    eul0001 ->SetLineColor(kYellow);

    eul01   ->SetTitle("h=0.1 s");
    eul001  ->SetTitle("h=0.01 s");
    eul0001 ->SetTitle("h=0.001 s");

    mgr->SetTitle("Eulero diversi passi h");
    mgr->GetXaxis()->SetTitle("Tempo t [s]");
    mgr->GetYaxis()->SetTitle("Posizione x [m]");

    mgr->Draw("ALP");
    c->BuildLegend();
    /* TLegend *mylegend{new TLegend(0.2, 0.6, 0.4, 0.8)};
    mylegend->AddEntry(senx, "Sen(x)", "LP");
    mylegend->AddEntry(eul01, "h = 0.1 s", "LP");
    mylegend->AddEntry(eul001, "h = 0.01 s", "LP");
    mylegend->AddEntry(eul0001, "h = 0.001 s", "LP");

    mylegend->Draw();
     */
    myApp.Run();

    return 0;
}