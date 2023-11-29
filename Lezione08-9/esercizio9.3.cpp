#include "differenzia.hpp"
#include "vettoriale.hpp"
#include <iostream>
#include <string>
#include <cassert>

#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"

using namespace std;

double interp(double x1, double y1, double x2, double y2, double y=0);
double interp(vector<vector<double>> val, double y=0);
vector<vector<double>> search_inv(EquazioneDifferenzialeBase &eq, FunzioneVettorialeBase &fun, const double &h, vector<double> x={0.,0.});

bool are_close(double, double);
void test_runge_kutta();

int main(int argc, const char** argv){
    if(argc!=3){
        cerr << "Uso del programma " << argv[0] << " <passo> <lunghezza>" << endl;
        exit(-1);
    }

    Kutta kut;

    double h{atof(argv[1])};
    double t{0.};
    double s{0.1};
    TGraph *g_periodo = new TGraph;
    for(int i{0}; i<30; i++){
        double amp{s*(double)(i+1)};
        Pendolo pen(amp, 9.81);
        pen.setLength(atof(argv[2]));
        vector<vector<double>> result{search_inv(kut, pen, h, {amp, 0.})};
        g_periodo->SetPoint(i, amp, 2.*fabs(interp(result)));
    }
    TCanvas can1;
    can1.cd();
    string title = "Pendolo l = ";
    title+=argv[2]; 
    title+=" m, h = ";
    title+=to_string(h);
    g_periodo->SetTitle(title.c_str());
    g_periodo->GetXaxis()->SetTitle("Ampiezza [rad]");
    g_periodo->GetYaxis()->SetTitle("Periodo [s]");
    g_periodo->Draw("AL*");
    can1.Print("periodo.png");    
    return 0;
}


double interp(double x1, double y1, double x2, double y2, double y){
    //cerr << "valori " << x1 << " " << x2 << " " << y1 << " " << y2 << " " << y << endl; 
    return x1+((x1-x2)/(y1-y2))*(y-y1);
}
double interp(vector<vector<double>> val, double y){
    //cerr << "vettore " << val[0][0] << " " << val[1][0] << " " << val[0][1] << " " << val[1][1] << " " << y << endl; 
    return val[0][0]+((val[0][0]-val[1][0])/(val[0][1]-val[1][1]))*(y-val[0][1]);
}

vector<vector<double>> search_inv(EquazioneDifferenzialeBase &eq, FunzioneVettorialeBase &fun, const double &h, vector<double> x){
    double v;
    double t{0.};
    while(true){
        v=x[1];
        x=eq.Passo(t, x, h, fun);
        if(v*x[1]<0){
            //cerr << v << " " << t-h << " " << x[1] << " " << t << endl; 
            return {{t-h, v},{t, x[1]}};
        }
        t+=h;
    }
}

bool are_close(double calculated, double expected) {
  double epsilon = 1e-7;
  return fabs(calculated - expected) < epsilon;
}

void test_runge_kutta() {
  Kutta rk;
  OscillatoreArmonicoSemplice oa{1.0};
  const double lastt{70.0};
  const double h{0.1};
  const int nsteps{static_cast<double>(lastt / h + 0.5)};
  std::vector<double> pos{0.0, 1.0};

  // Esegue la simulazione
  double t{};
  for (int idx{}; idx < nsteps; ++idx) {
    pos = rk.Passo(t, pos, h, oa);
    t += h;
  }

  assert(are_close(pos[0], 0.7738501114078689));
  assert(are_close(pos[1], 0.6333611095194112));
}