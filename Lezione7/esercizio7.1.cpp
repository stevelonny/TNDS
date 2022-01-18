#include "integratore.hpp"

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "fmtlib.h"
#include <cassert>

using namespace std;

bool are_close(double calculated, double expected);
void test_midpoint();

int main(int argc, const char** argv){

    if(argc != 3){
        fmt::print(stderr, "Troppi pochi argomenti!\nUso del programma: {0} <max_passi> <larghezza_passi>\nVerrà creata una tabella di <max_passi>/<larghezza_passi> righe, con ogni riga che riassume <larghezza_passi>\n", argv[0]);
        exit(-1);
    }
    TGraph * midgraph = new TGraph; 
    TGraph * simgraph = new TGraph;
    int maxstep{atoi(argv[1])};
    int passo{atoi(argv[2])};
    test_midpoint();
    int cfr = (log10(maxstep)>8?log10(maxstep):8);
    Seno sen;
    Midpoint mid;
    Simpson sim;
    fmt::print("{0:<{4}s} || {1:<9s} {5:<4s} | {2:<14s} | {3:<8s} {5:<5s} || {1:<9s} {6:<4s} | {7:<14s} | {3:<8s} {6:<5s}\n",
                "N. Passi"/*0*/, "Larghezza"/*1*/, "Midpoint"/*2*/, "Delta"/*3*/, cfr/*4*/, "Mid"/*5*/, "Sim"/*6*/, "Simpson"/*7*/);
    double intemp{};
    double intesp{};
    double max{}, min{};
    for(int i=passo; i<=maxstep+1; i+=passo){
        intemp = mid.Integrate(0, M_PI, i, sen);
        intesp = sim.Integrate(0, M_PI, i, sen);
        max = (i==passo?fabs(intemp-2):max);
        //cout << inte << " ";
        //cout << delta << endl;
        fmt::print("{0:<{4}} || {1:<14.12f} | {2:<14.12f} | {3:<14.12f} || {5:<14.12f} | {6:<14.12f} | {7:<14.12f}\n",
                  i, mid.getH(), intemp, fabs(intemp-2), cfr, sim.getH(), intesp, fabs(intesp-2));
        midgraph->SetPoint(i/passo, i, fabs(intemp-2.));
        simgraph->SetPoint(i/passo, i, fabs(intesp-2.));
        min = fabs(intesp-2);
    }   
    TCanvas can("Errori", "Errori", 800, 600);
    TMultiGraph sium("Errori", "Errori");
    midgraph->SetTitle("Midpoint");
    midgraph->SetMarkerColor(2);
    simgraph->SetTitle("Simpson");
    simgraph->SetMarkerColor(4);
    //sium.Add(midgraph);
    //sium.Add(simgraph);
    //midgraph->Draw("A*");
    //simgraph->Draw("*");
    can.cd();
    can.SetLogx();
    can.SetLogy();
    can.cd();
    simgraph->SetMinimum(min*1e-1);
    simgraph->SetMaximum(max*10);
    simgraph->GetXaxis()->SetLimits(passo-passo/2, maxstep+passo);
    simgraph->Draw("A*");
    can.cd();
    midgraph->Draw("*");
    can.Modified();
    midgraph->GetXaxis()->SetTitle("Numero di passi");
    midgraph->GetYaxis()->SetTitle("Errore");
    can.BuildLegend();
    can.SetTitle("Andamento Passi-Errore");
    can.Print("errori.png");
    return 0;
}

void test_midpoint(){
    Seno mysin;
    Midpoint mp;
    assert(are_close(mp.Integrate(0, M_PI, 10, mysin), 2.0082484079079745));
    assert(are_close(mp.Integrate(0, M_PI, 100, mysin), 2.000082249070986));
    assert(are_close(mp.Integrate(M_PI, 0, 10, mysin), -2.0082484079079745));
    assert(are_close(mp.Integrate(0, 1, 10, mysin), 0.45988929071851814));
    assert(are_close(mp.Integrate(1, 2, 30, mysin), 0.9564934239032155));
}

bool are_close(double calculated, double expected) {
  double epsilon = 1e-7;
  return fabs(calculated - expected) < epsilon;
}