#pragma once
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TImage.h"
#include "random.hpp"
#include "../../fmtlib.h"

#define FILENAME "soluzione.txt"

using namespace std;

class PonteAFilo {

    public:
        PonteAFilo() : m_rand(1), r_X{500.}, inc_l{0.002}, m_L{1.} {}
        ~PonteAFilo() {}

        void Esegui(double R){
            Calculate(R);
            m_l1 = m_rand.Gauss(r_l1, inc_l);
            m_R = m_rand.Gauss(R, inc_R);
            m_X = m_R*(m_L-m_l1)/m_l1;
        }

        double Analizza(double R, int n_volte = 1000){
            string title{fmt::format("ponte_R{0:>3.0f}", R)};
            FILE * file_out = fopen(FILENAME, "a+");
            vector<double> resistances;
            for(int i{0}; i<n_volte; i++){
                Esegui(R);
                resistances.push_back(m_X);
            }
            TH1F g_res(title.c_str(), title.c_str(), 100, *min_element(resistances.begin(), resistances.end()), *max_element(resistances.begin(), resistances.end()));
            for(int i{0}; i<n_volte; i++){
                g_res.Fill(resistances[i]);
            }
            g_res.StatOverflows(kTRUE);
            double dev{g_res.GetStdDev()};
            fmt::print("Resistenza R = {0:>4.0f} ohm, Valore ottenuto X = {1:<3.2f} +- {2:<3.2f}\n", R, g_res.GetMean(), dev);
            fmt::print(file_out, "Resistenza R = {0:>4.0f} ohm, Valore ottenuto X = {1:<3.2f} +- {2:<3.2f}\n", R, g_res.GetMean(), dev);
            TCanvas can("sium", "sium", 800, 600);
            can.cd();
            g_res.GetXaxis()->SetTitle("R [ohm]");
            g_res.GetYaxis()->SetTitle("N");
            g_res.Draw();
            can.Print((title+".png").c_str());
            return dev;
        }


    private:
        RandomGen m_rand;
        double r_X, m_X;
        double r_l1, m_l1;
        double m_R;
        double m_L;
        double inc_R, inc_l;
        void Calculate(double R){
            inc_R = R*5e-3;
            r_l1 = (R*m_L)/(r_X+R);
        }

};