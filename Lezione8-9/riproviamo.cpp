#include "differenzia.hpp"
#include "vettoriale.hpp"
#include <fstream>
#include <iostream>
#include <string>

#include "../fmtlib.h"


int main(int argc, const char** argv){

    if(argc!=1){

    }
    //Parametri base
    double h{atof(argv[1])};
    double omega0{atof(argv[2])};
    double ahpla{atof(argv[3])};
    double omega{atof(argv[4])};
    fmt::print("Valori passati:\nH={0}, omega0={1}, ahpla={2}, omega{3}\n",
                h, omega0, ahpla, omega);
    OscillatoreArmonicoForzato osc(omega0, (1./ahpla), omega);
    //Risolutore
    Kutta kut;
    double tmax{ahpla*15.};
    int nstep{(int)(tmax/h+.5)};
    vector<double> x{0., 0.};//vettore stato inizializzato a zero
    double t{0.};//tempo a 0
    for(int i{0}; i<nstep; i++){
        x = kut.Passo(t, x, h, osc);
        if(i!=nstep-1){
            t += h;
        }
    }
    vector<double> xinv{x};
    xinv = kut.Passo(tinv, )
    fmt::print("told = {0}, xold = {1}, vold = {2} | t = {3}, x = {4}, v = {5} || tinv = {6}, xinv = {7}, vint = {8}\n");
    return 0;
}

double interp(double x1, double y1, double x2, double y2, double y=0.){
    return x1+((x1-x2)/(y1-y2))*(y-y1);
}

void 
