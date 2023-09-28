#include <fstream>
#include <vector>
#include <iostream>
#include "../fmtlib.h"

#include "vettoriale.hpp"
#include "differenzia.hpp"

using namespace std;

int main(){

    Kutta kut;
    CalorimetroIdeale cal_ideal;
    CalorimetroReale cal_real;

    double tmax{600.};
    double h{0.01};
    int nstep{int(tmax/h+0.5)};
    double t{0.};
    vector<double> stat_ideal{cal_ideal.getT_10(), 0.};
    vector<double> stat_real{cal_real.getT_10(), 0.};
    
    for(int i{0}; i<nstep; i++){
        stat_ideal = kut.Passo(t, stat_ideal, h, cal_ideal);
        stat_real = kut.Passo(t, stat_real, h, cal_real);
        t += h;
        cout << "Passo numero " << i+1 << "/" << nstep << "\r";
        cout.flush();
    }
    cout << endl;
    fmt::print("Ultimo istante calcolato: {0:3.2f} s\n", t-h);
    fmt::print("Il vettore degli stati del calorimetro ideale:  T = {0:3.2f} K, dT/dt = {1:3.2f} K/s\n", stat_ideal[0], stat_ideal[1]);
    fmt::print("Il vettore degli stati del calorimetro reale:   T = {0:3.2f} K, d^2T/dt^2 = {1:3.2f} K/s^2\n", stat_real[0], stat_real[1]);

    return 0;
}