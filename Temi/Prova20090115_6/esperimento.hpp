#pragma once
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TImage.h"
#include "TF1.h"
#include "TH2F.h"
#include "TLegend.h"
#include <vector>

#include "random.hpp"
#include "../../fmtlib.h"

using namespace std;

class Glicerina {
    public:
        Glicerina() : 
            m_rand{1}, m_rho{2700.}, m_rho0{1250.}, m_g{9.81}, m_nu{0.83}, m_x{0.40} {
            }
        ~Glicerina() {}

        void Esegui(double R, double inc_t=0.01, double inc_R = 0.0001, double inc_x = 0.001) {
            m_vl = ((2*R*R)/(9.*m_nu))*(m_rho-m_rho0)*m_g;
            m_t = m_x/m_vl;
            
            m_x_mis = m_rand.Gauss(m_x, inc_x);
            m_t_mis = m_rand.Gauss(m_t, inc_t);
            m_R_mis = m_rand.Gauss(R, inc_R);
            m_vl_mis = m_x_mis/m_t_mis;
            m_nu_mis = ((2*m_R_mis*m_R_mis)/(9.*m_vl_mis))*(m_rho-m_rho0)*m_g;
        }

        void Analizza(int n_volte, double R, double inc_t=0.01, double inc_R = 0.0001, double inc_x = 0.001) {
            vector<double> v_nu;
            string title = fmt::format("nu, R={0}, inc_r={1}, inc_t={2}, inc_x={3}", R, inc_R, inc_t, inc_x);
            FILE *file_out = fopen("soluzione.txt", "a+");
            for(int i{0}; i<n_volte; i++){
                Esegui(R, inc_t, inc_R, inc_x);
                v_nu.push_back(m_nu_mis);
            }
            TH1F histo_nu(title.c_str(), title.c_str(), 100, *min_element(v_nu.begin(), v_nu.end()), *max_element(v_nu.begin(), v_nu.end()));
            for(int i{0}; i<v_nu.size(); i++){
                histo_nu.Fill(v_nu[i]);
            }
            histo_nu.StatOverflows(kTRUE);
            fmt::print("nu_mis = {0:>1.4f} +- {1:>1.4f}, R={2}, inc_r={3}, inc_t={4}, inc_x={5}\n", histo_nu.GetMean(), histo_nu.GetStdDev(), R, inc_R, inc_t, inc_x);
            fmt::print(file_out, "nu_mis = {0:>1.4f} +- {1:>1.4f}, R={2}, inc_r={3}, inc_t={4}, inc_x={5}\n", histo_nu.GetMean(), histo_nu.GetStdDev(), R, inc_R, inc_t, inc_x);
            
            TCanvas can("sium", "sium", 800, 600);
            can.cd();
            histo_nu.GetXaxis()->SetTitle("nu [kg*m^1*s^1]");
            histo_nu.GetYaxis()->SetTitle("N");
            histo_nu.Draw();
            can.Print((title+".png").c_str());
        }


    private:
        RandomGen m_rand;
        double m_rho, m_rho0;
        double m_g;
        double m_nu;
        double m_R;
        double m_x, m_t;
        
        double m_vl, m_vl_mis, m_x_mis, m_t_mis, m_R_mis;

        double m_nu_mis;
};