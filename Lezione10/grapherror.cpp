#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TF1.h"
#include "TLegend.h"
#include "TImage.h"
#include "../fmtlib.h"

#include "montecarlo.hpp"

using namespace std;

int main(int argc, const char** argv){
    if(argc!=2){
        fmt::print(stderr, "Sintassi errata! Uso del programma: {0} <precisione richiesta>\n", argv[0]);
        exit(-1);
    }
    ifstream file_in;
    file_in.open("errors.txt");
    if(file_in.fail()){
        fmt::print(stderr, "Errore nella lettura del file!\n");
        exit(-2);
    }
    int tsize;
    double terr;
    TCanvas can("can", "errors");
    TGraph gerror;
    int c{0};
    fmt::print("{0:>5} | {1:>11} | {2:>7}\n", "N", "Std Dev", "k parz");
    TF1 * funfit = new TF1("fit", "[0]/sqrt(x)", 90, 10010);
    double sum{0};
    while(file_in >> tsize >> terr){
        c++;
        //funfit->SetParameter(0, sqrt(tsize)*terr);
        fmt::print("{0:>5} | {1:>11} | {2:>7.5f}\n", tsize, terr, sqrt(tsize)*terr);
        sum+=sqrt(tsize)*terr;
        gerror.SetPoint(c, tsize, terr);
    }
    sum/=(double)c;
    //TF1 * funfit = new TF1("fit", "[0]/sqrt(x)", 100, 10000);
    //funfit->SetParameter(0, sum);
    gerror.Fit(funfit, "", "", 90, 10010);
    double k{funfit->GetParameter(0)};
    fmt::print("\nParametro k andamento Errore-N: {0}\n", k);
    fmt::print("Punti necessari per arrivare alla precisione richiesta: {0}\n", (int)pow((k/atof(argv[1])), 2));
    can.cd();
    gerror.SetTitle("Errore-N");
    gerror.GetXaxis()->SetTitle("N");
    gerror.GetYaxis()->SetTitle("Errore");
    //funfit->Draw("C");
    gerror.Draw("*");
    can.BuildLegend();
    can.Print("errors.png");

    return 0;
}