#include "solutore.hpp"

#include "fmtlib.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, const char** argv){

    if(argc != 4){
        fmt::print(stderr, "Troppi pochi argomenti!\n Uso del programma: {0} <prec minima> <prec massima> <max iterazioni>\n", argv[0]);
        exit(-1);
    }

    Bisezione bis;
    Secante sec;

    Parabola fun(-0.3, -1.392, 1.83528);

    vector<double> bisezione;
    vector<double> bisrprec;
    vector<bool> bisfound;
    vector<int> bisite;
    vector<double> secante;
    vector<double> secrprec;
    vector<bool> secfound;
    vector<int> secite;
    
    int x_min{-5};
    int x_max{-6};
    double prec{atof(argv[1])};
    int minprec = round(-log10(atof(argv[1])));
    cout << minprec << " ";
    int max{atoi(argv[3])};
    int cfrmax = (round(log10(max)+0.5)>3?round(log10(max)+0.5):3);
    int maxprec = round(-log10(atof(argv[2])));
    cout << maxprec << endl;
    int j = minprec;
    int i{0};
    fmt::print("{0:<5s} || {1:<{7}s} | {2:<5s} | {3:<{8}s} | {9:<8s} || {4:<{7}s} | {2:<5s} | {3:<{8}s} | {9:<8s} || {5:<13s} | {6:<15s}\n",
                "prec", "Bisezione", "Found", "nit", "Secante", "Delta*prec^-1", "Corrispondono?", 2+maxprec+minprec, cfrmax, "RPrec");
    for(j; j<=maxprec; j++){
        i=j-minprec;
        bisezione.push_back(bis.CercaZeriReference(x_min, x_max, fun, prec, max));
        bisrprec.push_back(bis.getRPrec());
        bisfound.push_back(bis.getFound());
        bisite.push_back(bis.getNIterations());
        secante.push_back(sec.CercaZeriReference(x_min, x_max, fun, prec, max));
        secrprec.push_back(sec.getRPrec());
        secfound.push_back(sec.getFound());
        secite.push_back(sec.getNIterations());
        fmt::print("{0:<5.0e} || {1:<{9}.{10}f} | {2:<5s} | {3:<{11}} | {12:<8.1e} || {4:<{9}.{10}f} | {5:<5s} | {6:<{11}} | {13:<8.1e} || {7:>13.1f} | {8:<9s}\n",
                    prec, bisezione[i], (bisfound[i]?"Sì":"No"), bisite[i], secante[i], (secfound[i]?"Sì":"No"), secite[i], fabs(bisezione[i]-secante[i])*(1/prec), (abs(bisezione[i]-secante[i])<prec?"Sì":"No"),
                    2+maxprec+minprec, (int)(-log10(prec)), cfrmax, bisrprec[i], secrprec[i]);
        prec*=1e-1;
    }
    fmt::print("{0:<5s} || {1:<{7}s} | {2:<5s} | {3:<{8}s} | {9:<8s} || {4:<{7}s} | {2:<5s} | {3:<{8}s} | {9:<8s} || {5:<13s} | {6:<15s}\n",
                "prec", "Bisezione", "Found", "nit", "Secante", "Delta*prec^-1", "Corrispondono?", 2+maxprec+minprec, cfrmax, "RPrec");
    fmt::print("Precisione finale: {0:5.0e} Massime iterazioni: {1}\n", prec*1e+1, max);

    return 0;
}