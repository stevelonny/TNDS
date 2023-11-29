#include "differenzia.hpp"
#include "vettoriale.hpp"
#include "random.hpp"
#include "stats.hpp"
#include "../../fmtlib.h" /*  */

#include <iostream>
//#include <fstream>
//#include <string>

/* #include "TMultiGraph.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
 */

using namespace std;

int main(){

    Kutta kut;

    OscillatoreArmonicoForzato osc(1.15, 0.01, 0.);

    vector<double> stat{1., 0.};            /* Vettore con condizioni iniziali per il problema di Cauchy */
    vector<double> stat_double{1., 0.};     /* Secondo vettore per il calcolo della precisione */
    double tmax{43.};                       /* Tempo fino cui integrare */
    double t{0.};                           /* Istante di tempo lungo cui integrare */
    double h{0.5};                          /* Passo scelto inizialmente */
    
    int nstep{int(tmax/h+0.5)};             /* Numero di step per il passo iniziale scelto */
    for(int i=0; i<nstep; i++){
        stat = kut.Passo(t, stat, h, osc);                      /* Integrale normale */
        t += h;
    }
    t = 0.;
    h /= 2.;
    nstep = int(tmax/h+0.5);        /* Doppio dei passi, che equivale ad avere il doppio della precisione */
    for(int i=0; i<nstep; i++){
        stat_double = kut.Passo(t, stat_double, h, osc);                      /* Integrale con il doppio dei passi */
        t += h;
    }

    fmt::print("Posizione x al tempo t = 43 s : x = {0:5.4f} con passo {1} ;\nCon doppia precisione (doppio dei passi) x =: {2:5.4f} ;\n", stat[0], h*2., stat_double[0]);
    fmt::print("Con errore di e = {0:5.4f}\n", (16./15.)*fabs(stat[0]-stat_double[0]));     /* Errore commesso con h = 0.01 */
    double h_fifty{pow(((15./16.)*((h*h*h*h)/fabs(stat[0]-stat_double[0])))*50e-6, 1./4.)}; /* Passo stimato a partire dall'errore commesso con h = 0.01 */
    fmt::print("Passo necessario per avere una precisione di 50 um: {0:5.4f}\n", h_fifty);

    RandomGen rand(1);
    vector<double> prec{0.5, 1.0, 1.5, 2.0, 3.0};
    vector<double> values;
    nstep = (int(tmax/h_fifty+0.5));
    fmt::print("{0:<7s} || {1:<7s} | {2:<7s} \n",
                "Err x_0", "Media", "Dev Std");
    for(int i=0; i<prec.size(); i++){ /* Primo ciclo, per ogni precisione su x_0 richiesta */
        values.clear();
        for(int k=0; k<1000; k++){ /* Secondo ciclo, 1000 iterazione per ogni valore estratto dalla gaussiana con centro x_0 */
            t = 0.;
            fmt::print("{0:>7.1f} || calcolo numero: {1}/1000 \r", prec[i],  k+1);
            stat = {rand.Gauss(1., prec[i]), 0.}; /* Assegniamo a caso nella gaussiana il valore iniziale */
            for(int j=0; j<nstep; j++){ /* Ciclo più interno per integrare davvero, usando il passo trovato prima */
                stat = kut.Passo(t, stat, h_fifty, osc); 
                t += h;
            }
            values.push_back(stat[0]);
            std::fflush(stdout);
        }
        fmt::print("                                                \r");
        fmt::print("{0:>7.1f} || {1:<7.3f} | {2:<7.3f} \n",
                    prec[i], Mean(values), StdDev(values)); /* Funzioni prese da stats.hpp, funzioni di statistica */
    }

    return 0;

}
