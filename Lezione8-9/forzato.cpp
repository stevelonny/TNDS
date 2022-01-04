#include "differenzia.hpp"
#include "vettoriale.hpp"
#include <fstream>
#include <iostream>
#include <string>

#include "../fmtlib.h"

vector<vector<double>> search_inv(EquazioneDifferenzialeBase &eq, FunzioneVettorialeBase &fun, const double &h, double t, vector<double> x);
double interp(double x1, double y1, double x2, double y2, double y=0);
double interp(vector<vector<double>> val, double y=0);

int main(int argc, const char** argv){

    if(argc!=4){
        cerr << "Uso del programma " << argv[0] << " <passo> <omega0> <alpha^-1>" << endl;
        exit(-1);
    }
    //Costruiamo l'oscillatore e l'integratore
    vector<double> x{0.,0.};
    double t{0.};
    double tinv;
    double h{atof(argv[1])};
    double omega0{atof(argv[2])};
    double ahpla{atof(argv[3])};
    double omega{omega0-1.+0.01};
    OscillatoreArmonicoForzato osc(omega0, 1./ahpla, omega);
    Kutta kut;
    double tmax{ahpla*15.};
    int nstep{(int)tmax/h+.5};
    //Vettori d'ausilio
    vector<double> xtemp{0.,0.};
    vector<vector<double>> amp(21);
    vector<vector<double>> temp2{{0.,0.,0.},{0.,0.,0.}};
    vector<vector<double>> sium(21);
    //Intestazione tabella
    fmt::print("{0:<5} | {1:<6} | {2:<15} | {8:<15} | {3:<6} | {4:<15} | {9:<15} | {5:<6} | {10:<8} | {6:<15} | {7:<14} \n",
                "Freq", "t_0", "om_0", "t_1", "om_1", "tinv", "om_inv", "amp", "amp_0", "amp_1", "newh");
    //Output omega e ampiezze
    ofstream file_out;
    file_out.open("freq.txt");
    //Cicli per tutto
    for(int i=0; i<21; i++){
        //Arriviamo fino a 15*(1/alpha)
        for(int j=0; j<nstep; j++){
            x = kut.Passo(t, x, h, osc);
            t+=h;
        }
        sium[i] = {omega, t-h, x[0], x[1]};
        t-=h; //Torniamo indietro di un passo h che corrisponde all'ultimo stato calcolato
        //Cerchiamo il momento in cui la velocità si inverte
        temp2 = search_inv(kut, osc, h, t, x);
        tinv = interp(temp2, 0.);
        //Esploriamo fino a trovare il max teorico
        xtemp = kut.Passo(t, x, tinv-t, osc);
        amp[i] = {omega, xtemp[0], xtemp[1]};
        fmt::print(
        "{0:<5.2f} | {1:<5.2f} | {2:<15.12f} | {7:<15.12f} | {3:<5.2f} | {4:<15.12f} | {8:<15.12f} | {5:<5.2f} | {10:<9.6f} | {6:<15.12f} | {9:<15.12f} \n",
        /*0*/omega,/*1*/temp2[0][0],/*2*/temp2[0][1],/*3*/temp2[1][0],/*4*/temp2[1][1],/*5*/tinv,/*6*/xtemp[1],/*7*/temp2[0][2],/*8*/temp2[1][2],/*9*/xtemp[0],/*10*/tinv-t);
        //freq    ,t0              ,v0              ,t1              ,v1              ,tinv     ,vinv         ,amp0         ,amp1            ,amp             ,tinv-t or newh
        file_out << xtemp[1] << '\t'<< '\t' << xtemp[0] << endl;
        t=0;
        x={0.,0.};
        omega=osc.getOmega()+0.1;
        osc.setOmega(omega);
    }

    return 0;
}

vector<vector<double>> search_inv(EquazioneDifferenzialeBase &eq, FunzioneVettorialeBase &fun, const double &h, double t, vector<double> x){
    double v, xold;
    while(true){
        xold=x[0];
        v=x[1];
        x=eq.Passo(t, x, h, fun);
        if(v*x[1]<0){
            //cerr << v << " " << t-h << " " << x[1] << " " << t << endl; 
            return {{t-h, v, xold},{t, x[1], x[0]}};
        }
        t+=h;
    }
}

double interp(double x1, double y1, double x2, double y2, double y){
    //cerr << "valori " << x1 << " " << x2 << " " << y1 << " " << y2 << " " << y << endl; 
    return x1+((x1-x2)/(y1-y2))*(y-y1);
}
double interp(vector<vector<double>> val, double y){
    //cerr << "vettore " << val[0][0] << " " << val[1][0] << " " << val[0][1] << " " << val[1][1] << " " << y << endl; 
    return val[0][0]+((val[0][0]-val[1][0])/(val[0][1]-val[1][1]))*(y-val[0][1]);
}