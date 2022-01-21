#include "differenzia.hpp"
#include "vettoriale.hpp"
#include "../fmtlib.h"

#include <iostream>
#include <string>

#include "TMultiGraph.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"

using namespace std;

int main(){

    TApplication app("app", 0, 0);

    Kutta kut;
    Eulero eul;
    OscillatoreArmonicoSemplice osc;
    osc.setOmega(1);
    double tmax{70};
    double h{0.001};
    TGraph * gkutta = new TGraph;
    TGraph * geulero = new TGraph;
    double max, min;
    double hmin{0.001};
    double hmax{0.129};
    double hh{2};
    int c{0};
    fmt::print(" {0:5} | {1:>10} | {2:>10} | \n", "Passo", "Err Eulero", "Err Kutta");
    for(double h=0.001; h<hmax; h*=2.){
        vector<double> xk{0., 1.};
        vector<double> xe{0., 1.};
        double t{0.};
        //cout << h;
        int nstep{int(tmax/h+0.5)};
        for(int i=0; i<nstep; i++){
            xk = kut.Passo(t, xk, h, osc);
            xe = eul.Passo(t, xe, h, osc);
            t += h;
        }
        c++;
        //cout << " " << fabs(sin(tmax)-xk[0]) << " " << fabs(sin(tmax)-xe[0]) << endl;
        fmt::print(" {0:1.3f} | {1:>10.2e} | {2:>10.2e} | \n", h, fabs(sin(tmax)-xe[0]), fabs(sin(tmax)-xk[0]));
        gkutta->SetPoint(c, h, fabs(sin(tmax)-xk[0]));
        geulero->SetPoint(c, h, fabs(sin(tmax)-xe[0]));
    }
    max = geulero->GetMaximum();
    min = gkutta->GetMinimum();
    gkutta->SetTitle("Kutta");
    gkutta->SetMarkerColor(2);
    gkutta->SetLineColor(2);
    geulero->SetTitle("Eulero");
    geulero->SetMarkerColor(4);
    geulero->SetLineColor(4);
    TMultiGraph * mgraph = new TMultiGraph;
    mgraph->Add(gkutta);
    mgraph->Add(geulero);
    TCanvas * can = new TCanvas("Errori", "Errori", 800, 600);
    can->cd();
    
    //geulero->SetMaximum(max);
    //geulero->SetMinimum(min);
    can->Modified();
    mgraph->SetTitle("Errori");
    mgraph->GetXaxis()->SetTitle("Numero di passi");
    mgraph->GetYaxis()->SetTitle("Errore");
    mgraph->Draw("A*");
    //geulero->Draw("A*");
    //gkutta->Draw("*");
    can->SetLogx();
    //can->SetLogy();
    mgraph->Draw("ALP*");
    can->Modified();
    can->BuildLegend();
    
    //can->Print("errori.png");
    app.Run();
    return 0;
}