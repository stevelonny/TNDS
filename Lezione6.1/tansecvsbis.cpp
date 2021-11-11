#include "solutore.hpp"
#include "fmtlib.h"

#include <vector>
#include <iomanip>

using namespace std;

int main(int argc, const char** argv){
    if(argc!=3){
        fmt::print(stderr, "Troppi pochi argomenti!\n");
        fmt::print(stderr, "Uso del programma : {0} <prec> <max ite>\n", argv[0]);
        exit(-1);
    }
    unsigned int max = (atoi(argv[2]) > 0 ? atoi(argv[2]) : 100);
    double prec = atof(argv[1]);
    int cfrmax = (round(log10(max)+0.5)>3?round(log10(max)+0.5):3);
    x_Tanx fun;
    Bisezione sol;
    vector<double> valori;
    vector<double> valoriprec;
    vector<bool> valfound;
    vector<int> valite;
    vector<double> valsec;
    vector<double> valsecprec;
    vector<bool> valsecfound;
    vector<int> valsecite;
    Secante sec;
    fmt::print("{0:<2s} || {1:<{7}s} | {2:<5s} | {3:<{8}s} | {9:<8s} || {4:<{7}s} | {2:<5s} | {3:<{8}s} | {9:<8s} || {5:<13s} | {6:<15s}\n",
                "n", "Bisezione", "Found", "nit", "Secante", "Delta*prec^-1", "Corrispondono?", 3+(int)(-log10(prec)), cfrmax, "RPrec");
    for(int i=0; i<20; i++){
        valori.push_back(sol.CercaZeriReference(i*M_PI, i*M_PI+M_PI_2, fun, prec, max));
        valoriprec.push_back(sol.getRPrec());
        valfound.push_back(sol.getFound());
        valite.push_back(sol.getNIterations());
        valsec.push_back(sec.CercaZeriReference(i*M_PI, i*M_PI+M_PI_2, fun, prec, max));
        valsecprec.push_back(sec.getRPrec());
        valsecfound.push_back(sec.getFound());
        valsecite.push_back(sec.getNIterations());
        fmt::print("{0:<2} || {1:>{9}.{10}f} | {2:<5s} | {3:<{11}} | {12:<8.1e} || {4:>{9}.{10}f} | {5:<5s} | {6:<{11}} | {13:<8.1e} || {7:>13.1f} | {8:<9s}\n",
                    i+1, valori[i], (valfound[i]?"Sì":"No"), valite[i], valsec[i], (valsecfound[i]?"Sì":"No"), valsecite[i], (valori[i]-valsec[i])*(1/prec), (abs(valori[i]-valsec[i])<prec?"Sì":"No"),
                    3+(int)(-log10(prec)), (int)(-log10(prec)), cfrmax, valoriprec[i], valsecprec[i]);
    }
    fmt::print("Precisione passata: {0} Massime iterazioni: {1}\n", prec, max);
    return 0;
}