#include "differenzia.hpp"
#include "vettoriale.hpp"
#include <iostream>
#include <string>

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"

using namespace std;

double interp(double x1, double y1, double x2, double y2, double y=0);

int main(int argc, const char** argv){
    if(argc!=4){
        cerr << "Uso del programma " << argv[0] << " <passo> <lunghezza> <ampiezza>" << endl;
        exit(-1);
    }

    TApplication myApp("myApp", 0, 0);

    Kutta kut;

    Pendolo pen(atof(argv[2]), 9.8);
    double h{atof(argv[1])};
    vector<double> x{(atof(argv[3])), 0};
    double t{0.};
    double v{x[1]};
    int c{0};
    int ind;
    TGraph *posizione{new TGraph};
    TGraph *velocita{new TGraph};
    vector<double> pos;
    vector<double> vel;
    vector<double> ist;
    //cerr << "check " << x[0] << " " << x[1] << " " << pen.getLength() << " " << pen.getG() << endl;
    while(true){
        v = x[1];
        pos.push_back(x[0]);
        vel.push_back(x[1]);
        ist.push_back(t);
        x = kut.Passo(t,x,h,pen);
        if(v*x[1]<0){
            ind = c-1;
            break;
        }
        t += h;
        c++;
    }
    double periodo{2.*fabs(interp(ist[ind], vel[ind], ist[ind+1], vel[ind+1]))};
    cout << "Periodo: " << periodo << endl;
    t = 0;
    x = {(atof(argv[3])), 0};
    int nstep{int((4.*periodo)/h+0.5)};
    for(int i=0; i<nstep; i++){    
        posizione->SetPoint(i, t, x[0]);
        velocita->SetPoint(i, t, x[1]);
        x = kut.Passo(t,x,h,pen);
        t += h;
    }
    
    TCanvas can1;
    can1.cd();
    string title = "Pendolo l = ";
    title+=argv[2]; 
    title+=" m, h = ";
    title+=to_string(h);
    posizione->SetTitle(title.c_str());
    posizione->GetXaxis()->SetTitle((((string)("(T=")+to_string(periodo)+" s)"+"Tempo t [s]")).c_str());
    posizione->GetYaxis()->SetTitle((((string)("(Amp0=")+argv[3]+" rad)"+"Posizione [rad]")).c_str());
    posizione->Draw("AL");
    TCanvas can2;
    can2.cd();
    string titled = "Pendolo l = ";
    titled+=argv[2]; 
    titled+=" m, h = ";
    titled+=to_string(h);
    velocita->SetTitle(title.c_str());
    velocita->GetXaxis()->SetTitle((((string)("(T=")+to_string(periodo)+" s)"+"Tempo t [s]")).c_str());
    velocita->GetYaxis()->SetTitle("(V0=0)Velocità [rad/s]");
    velocita->Draw("AL");
    //TMultiGraph *mgr{new TMultiGraph};
    //mgr->Add(posizione);
    //mgr->Add(velocita);
    //mgr->Draw("ALP");
    myApp.Run();
    
    return 0;
}


double interp(double x1, double y1, double x2, double y2, double y){
    return x1+((x1-x2)/(y1-y2))*(y-y1);
}