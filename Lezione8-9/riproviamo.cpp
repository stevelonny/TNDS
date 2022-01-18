#include "differenzia.hpp"
#include "vettoriale.hpp"

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"

#include <fstream>
#include <iostream>
#include <string>

#include "../fmtlib.h"

double sign(double x);
int search_inv(vector<vector<double>> values, double ahpla, double h);
double interp(double x1, double y1, double x2, double y2, double y=0.);

int main(int argc, const char** argv){

    if(argc!=4){
        cerr << "Uso del programma " << argv[0] << " <passo> <omega0> <alpha^-1>" << endl;
        exit(-1);
    }
    //Parametri base per l'oscillaore
    double h{atof(argv[1])};
    double omega0{atof(argv[2])};
    double ahpla{atof(argv[3])};
    fmt::print("Valori passati: H = {0}, omega0 = {1}, ahpla = {2}\n",
                h, omega0, ahpla);
    //TGraph
    TGraph graph;
    //Parametri necessari per il risolutore
    vector<double> s{0, 0};
    double t{0};
    double tmax{15.*ahpla};
    int nstep{(int)(tmax/h+.5)};
    //Settiamo oscillatore e risolutore
    double omega{omega0-1.+0.01};
    OscillatoreArmonicoForzato osc(omega0, 1./ahpla, omega);
    Kutta kut;
    //El Ciclo
    fmt::print("{0:7} | {1:6} | {2:8} | {3:6} | {4:8} | {5:6} | {6:8} | {7}\n", "Freq", "t0", "v0", "t1", "v1", "tinv", "vinv", "amp");
    for(int i{0}; i<21; i++){
        osc.setOmega(omega);
        //Settiamo contatore tempo e vettore degli stati a 0
        t = 0.;
        s = {0., 0.};
        //Creiamo un vettore per contenere tutti i passi calcolati fino a 15*alpha-1
        vector<vector<double>> values(nstep);
        for(int j{0}; j<nstep; j++){
            s = kut.Passo(t, s, h, osc);
            t+=h;
            values[j] = {t, s[0], s[1]};
        }
        //Cerchiamo l'indice corrispondente all'inversione dopo un tempo ragionevole (messo come 10*alpha-1)
        int inv = (search_inv(values, ahpla, h));
        //Troviamo l'effettivo valore dell'istante di tempo con una interpolazione
        double t_inv{interp(values[inv][0], values[inv][2], values[inv+1][0], values[inv+1][2])};
        //Troviamo l'ampiezza a tale tinv con kutta
        s = {values[inv][1], values[inv][2]};
        s = kut.Passo(values[inv][0], s, t_inv-values[inv][0], osc);
        //Aggiungiamo i punti al grafico
        graph.SetPoint(i, omega, fabs(s[0]));
        fmt::print("{0:>7.2f} | {1:3.2f} | {2:8.5f} | {3:3.2f} | {4:8.5f} | {5:3.2f} | {6:8.5f} | {7:>5.2f}\n", omega, values[inv][0], values[inv][2], values[inv+1][0], values[inv+1][2], t_inv, s[1], s[0]);
        //Cicliamo
        omega+=0.1;
    }
    //ROOT yay
    TCanvas can("Risonanza", "Risonanza", 800, 600);
    can.cd();
    graph.SetTitle("Pulsazione-Ampiezza");
    graph.GetXaxis()->SetTitle("Pulsazione [rad/s]");
    graph.GetYaxis()->SetTitle("Ampiezza [rad]");
    graph.Draw("APL*");
    can.Print("risonanza_bis.png");

    return 0;
}

//Interpolazione (y=0.)
double interp(double x1, double y1, double x2, double y2, double y){
    return x1+((x1-x2)/(y1-y2))*(y-y1);
}
//Ricerca dell'indice dove avviene una inversione
int search_inv(vector<vector<double>> values, double ahpla, double h){
    //Settiamo i limiti della ricerca
    int minstep{(int)(((10*ahpla)/h)+0.5)};
    int maxstep{(int)(((15.*ahpla)/h)+0.5)};
    //Conserviamo il primo valore
    double v_old{values[minstep][2]};
    for(int i{minstep}; i<values.size(); i++){
        if(sign(values[i][2])*sign(v_old) < 0){
            return i-1;
        }
        //Cicliamo
        v_old = values[i][2];
    }
    //Non dovrebbe succedere, ma se succede facciamo un po' di casino
    return -1;
}
//Copia il segno per evitare approssimazioni
double sign(double x){
    return x != 0 ? copysign(1.0, x) : 0.0; 
}