#include "resistenza.hpp"
#include "../../fmtlib.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TImage.h"
#include "TF1.h"
#include "TLegend.h"

using namespace std;

TGraph DoPlot(vector<double> x, vector<double> y, const char* title="title", const char* x_title="asse x", const char* y_title="asse y");

int main(int argc, const char ** argv){

    if(argc!=2){
        fmt::print(stderr, "Errore input! Uso del programma: {0} <n_simulazioni>\n", argv[0]);
        return -1;
    }
    FILE * file_out = fopen("soluzione.txt", "w+b");
    Resistenza resistance;
    vector<double> r_inc_try{1, 3, 5, 7, 9};
    vector<double> r_inc_std = resistance.Analizza(atoi(argv[1]));
    fmt::print(" {0:>5} | {1:>8} |\n", "R_inc", "R_in_inc");
    fmt::print(file_out, " {0:>5} | {1:>8} |\n", "R_inc", "R_in_inc");
    for(int i{0}; i<r_inc_try.size(); i++){
    fmt::print(" {0:>5} | {1:>8.2f} |\n", r_inc_try[i], r_inc_std[i]);
    fmt::print(file_out, " {0:>5} | {1:>8.2f} |\n", r_inc_try[i], r_inc_std[i]);
    }
    auto g_inc = DoPlot(r_inc_try, r_inc_std, "Andamento errore", "Inc usata [ohm]", "Inc risultante [ohm]");
    TF1 * fit = new TF1("fit", "[0]+[1]*x^[2]", *min_element(r_inc_try.begin(), r_inc_try.end())-0.5, *max_element(r_inc_try.begin(), r_inc_try.end())+0.5);
    g_inc.Fit(fit, "", "", *min_element(r_inc_try.begin(), r_inc_try.end())-0.5, *max_element(r_inc_try.begin(), r_inc_try.end())+0.5);
    fmt::print("\nParametri: p_0 = {0:1.2f}, p_1 = {1:1.2f}, p_2 = {2:1.2f}\n", fit->GetParameter(0), fit->GetParameter(1), fit->GetParameter(2));
    fmt::print(file_out, "Parametri: p_0 = {0:1.2f}, p_1 = {1:1.2f}, p_2 = {2:1.2f}\n", fit->GetParameter(0), fit->GetParameter(1), fit->GetParameter(2));
    fmt::print("Incertezza necessaria per ottenere R_inc = 3 ohm: {0:1.2f}\n", pow((3.-fit->GetParameter(0))/fit->GetParameter(1), 1./fit->GetParameter(2)));
    fmt::print(file_out, "Incertezza necessaria per ottenere R_inc = 3 ohm: {0:1.2f}\n", pow((3.-fit->GetParameter(0))/fit->GetParameter(1), 1./fit->GetParameter(2)));
    TCanvas can("Errore", "Errore", 800, 600);
    can.cd();
    g_inc.Draw("A*");
    can.Print("errori.png");

    return 0;
}

TGraph DoPlot(vector<double> x, vector<double> y, const char* title, const char* x_title, const char* y_title){
    if(x.size()!=y.size()){
        fmt::print(stderr, "wtf vettori diversa misura\n");
        exit(-2);
    }
    TGraph graph;
    for(int i{0}; i<x.size(); i++){
        graph.SetPoint(i, x[i], y[i]);
    }
    graph.SetTitle(title);
    graph.GetXaxis()->SetTitle(x_title);
    graph.GetYaxis()->SetTitle(y_title);

    return graph;
}
