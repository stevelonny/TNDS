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
#include "TH2F.h"
#include "TLegend.h"
#include <iostream>

using namespace std;


double interp(double x1, double y1, double x2, double y2, double y);


int main(){

    PuntoStrano point;    
    
    Eulero eul;

    vector<double> pos_0{1, 0, 0, -1};
    double t{0.};
    double period{2*M_PI};
    double tmax{10.*period};
    point.setAlpha(0.);    
    double prec{2.};
    double temp{0};
    double h{0.5};
    vector<vector<double>> h_x;
    int c{0};
    while(fabs(1.-temp)>0.1){
        t = 0;
        pos_0 = {1, 0, 0, -1};
        int n_step{round(tmax/h+0.5)};
        for(int i{0}; i<n_step; i++){
            pos_0 = eul.Passo(t, pos_0, h, point);
            t += h;
        }
        temp = pos_0[0];
        h_x.push_back({h, fabs(1.-temp)});
        fmt::print(" {0:>1.4f} | {1:>1.4f}\n", h_x[c][0], h_x[c][1]);
        h /= 2.;
        c++;
    }
    double realh{interp(h_x.back()[0], h_x.back()[1], h_x[c-2][0], h_x[c-2][1], 0.1)};
    cout << h_x.back()[0] << " " << h_x.back()[1] << " " << h_x.at(h_x.size()-1)[0] << " " << h_x.at(h_x.size()-1)[1] << endl;
    t = 0;
    pos_0 = {1, 0, 0, -1};
    int n_step{round(tmax/realh+0.5)};
    for(int i{0}; i<n_step; i++){
        pos_0 = eul.Passo(t, pos_0, realh, point);
        t += h;
    }
    temp = pos_0[0];
    fmt::print("eulero: passo h = {0:>1.4f}, valore = {1:>1.4f}, differenza = {2:>1.4f}\n", realh, temp, fabs(1.-temp));
    Kutta kut;
    t = 0;
    pos_0 = {1, 0, 0, -1};
    for(int i{0}; i<n_step; i++){
        pos_0 = kut.Passo(t, pos_0, realh, point);
        t += h;
    }
    temp = pos_0[0];
    fmt::print("kutta: passo h = {0:>1.6f}, valore = {1:>1.6f}, differenza = {2:>1.6f}\n", realh, temp, fabs(1.-temp));
    tmax = 2.*period;
    TGraph g_eul_meno;
    point.setAlpha(-1.);
    t = 0;
    pos_0 = {1, 0, 0, -1};
    for(int i{0}; i<n_step; i++){
        pos_0 = eul.Passo(t, pos_0, realh, point);
        t += h;
        g_eul_meno.SetPoint(i, pos_0[0], pos_0[1]);
    }
    TCanvas can("sium", "sium", 800, 600);
    can.cd();
    g_eul_meno.Draw("AL");
    can.Print("meno_uno_eulero.png");
    can.Clear();
    TGraph g_eul_plus;
    point.setAlpha(1.);
    t = 0;
    pos_0 = {1, 0, 0, -1};
    for(int i{0}; i<n_step; i++){
        pos_0 = eul.Passo(t, pos_0, realh, point);
        t += h;
        g_eul_plus.SetPoint(i, pos_0[0], pos_0[1]);
    }
    can.cd();
    g_eul_plus.Draw("AL"),
    can.Print("plus_uno_eulero.png");
    can.Clear();
    TGraph g_kut_plus;
    point.setAlpha(1.);
    t = 0;
    pos_0 = {1, 0, 0, -1};
    for(int i{0}; i<n_step; i++){
        pos_0 = kut.Passo(t, pos_0, realh, point);
        t += h;
        g_kut_plus.SetPoint(i, pos_0[0], pos_0[1]);
    }
    can.cd();
    g_kut_plus.Draw("AL"),
    can.Print("plus_uno_kutta.png");
    can.Clear();
    TGraph g_kut_meno;
    point.setAlpha(-1.);
    t = 0;
    pos_0 = {1, 0, 0, -1};
    for(int i{0}; i<n_step; i++){
        pos_0 = kut.Passo(t, pos_0, realh, point);
        t += h;
        g_kut_meno.SetPoint(i, pos_0[0], pos_0[1]);
    }
    can.cd();
    g_kut_meno.Draw("AL"),
    can.Print("meno_uno_kutta.png");
    can.Clear();
    
    
    return 0;
}

double interp(double x1, double y1, double x2, double y2, double y){
    //cerr << "valori " << x1 << " " << x2 << " " << y1 << " " << y2 << " " << y << endl; 
    return x1+((x1-x2)/(y1-y2))*(y-y1);
}