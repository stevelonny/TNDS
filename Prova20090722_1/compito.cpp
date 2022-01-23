#include "differenzia.hpp"
#include "../fmtlib.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TImage.h"
#include "TF1.h"
#include "TLegend.h"

using namespace std;

TGraph DoPlot(vector<double> x, vector<double> y, const char* title="title", const char* x_title="asse x", const char* y_title="asse y");

int main(){

    Kutta kut;
    ProtoneElettrico protone;
    
    vector<double> stat{0., 1e8};
    double tmax{1e-7};
    double h{1e-12};
    int n_step{round(tmax/h+0.5)};
    double t{0.};
    vector<double> vel;
    vector<double> time;
    for(int i{0}; i<n_step; i++){
        vel.push_back(kut.Passo(t, stat, h, protone)[1]);
        time.push_back(t);
        t+=h;
    }
    TGraph g_vel10e8 = DoPlot(time, vel, "Moto Uniforme?", "Tempo [s]", "Velocità [m/s]");
    TCanvas can("Vel", "Vel", 900, 600);
    can.cd();
    g_vel10e8.GetYaxis()->SetMaxDigits(2);
    g_vel10e8.Draw("AL");
    can.Print("vel.png");


    return 0;
}

TGraph DoPlot(vector<double> x, vector<double> y, const char* title, const char* x_title, const char* y_title){
    if(x.size()!=y.size()){
        fmt::print(stderr, "wtf vettori diversa misura\n");
        exit(-2);
    }
    TGraph graph;
    for(int i{0}; i<x.size(); i++){
        graph.SetPoint(i, x[i], y[i]);
    }
    graph.SetTitle(title);
    graph.GetXaxis()->SetTitle(x_title);
    graph.GetYaxis()->SetTitle(y_title);

    return graph;
}