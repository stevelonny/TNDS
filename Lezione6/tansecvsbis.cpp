#include "solutore.hpp"
#include "fmtlib.h"

#include <vector>
#include <iomanip>

using namespace std;

int main(){
    unsigned int max = 100;
    x_Tanx fun;
    Bisezione sol;
    vector<double> valori;
    vector<bool> valfound;
    vector<int> valite;
    vector<double> valsec;
    vector<bool> valsecfound;
    vector<int> valsecite;
    Secante sec;
    fmt::print("{0:<2s} || {1:<13s} | {2:<5s} | {3:<4s} || {4:<13s} | {2:<5s} | {3:<4s} || {5:<13s} | {6:<15s}\n",
                "n", "Bisezione", "Found", "nit", "Secante", "Distanza*10^6", "Corrispondono?");
    for(int i=0; i<20; i++){
        valori.push_back(sol.CercaZeriReference(i*M_PI, i*M_PI+M_PI_2, fun, 1e-6, max));
        valfound.push_back(sol.getFound());
        valite.push_back(sol.getNIterations());
        valsec.push_back(sec.CercaZeriReference(i*M_PI, i*M_PI+M_PI_2, fun, 1e-6, max));
        valsecfound.push_back(sec.getFound());
        valsecite.push_back(sec.getNIterations());
        fmt::print("{0:<2} || {1:>13.10f} | {2:<5s} | {3:<4} || {4:>13.10f} | {5:<5s} | {6:<4} || {7:>13.10f} | {8:<9s}\n",
                    i+1, valori[i], (valfound[i]?"Sì":"No"), valite[i], valsec[i], (valsecfound[i]?"Sì":"No"), valsecite[i], (valori[i]-valsec[i])*(1e6), (abs(valori[i]-valsec[i])<1e-6?"Sì":"No"));
    }
    return 0;
}