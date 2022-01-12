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
#include "../fmtlib.h"
#include <vector>

#include "random.hpp"

class EsperimentoPrisma{

    public:
        EsperimentoPrisma();
        ~EsperimentoPrisma();
        
        const double getInc(){return m_inc;}
        const double getLambda1(){return m_lambda1;}
        const double getLambda2(){return m_lambda2;}
        const double getAlpha(){return m_alpha;}
        const double getA(){return m_A;}
        const double getB(){return m_B;}
        const double getn1(){return m_n1;}
        const double getn2(){return m_n2;}
        const double getTheta0(){return m_th0;}
        const double getTheta1(){return m_th1;}
        const double getTheta2(){return m_th2;}
        const double getDelta1(){return m_dm1;}
        const double getDelta2(){return m_dm2;}

        const double getAMis(){return m_A_mis;}
        const double getBMis(){return m_B_mis;}
        const double getn1Mis(){return m_n1_mis;}
        const double getn2Mis(){return m_n2_mis;}
        const double getTheta0Mis(){return m_th0_mis;}
        const double getTheta1Mis(){return m_th1_mis;}
        const double getTheta2Mis(){return m_th2_mis;}
        const double getDelta1Mis(){return m_dm1_mis;}
        const double getDelta2Mis(){return m_dm2_mis;}

        void Esegui();
        void Analizza(unsigned int n_volte);

    private:
        RandomGen m_rand;
        //Valori di input
        double m_inc;
        double m_lambda1, m_lambda2;
        double m_alpha;
        double m_A, m_B;
        //Misura "reale"
        double m_th0;
        double m_n1, m_n2;
        double m_dm1, m_dm2;
        double m_th1, m_th2;
        //Dati generati
        double m_A_mis, m_B_mis;
        double m_n1_mis, m_n2_mis;
        double m_dm1_mis, m_dm2_mis;
        double m_th0_mis, m_th1_mis, m_th2_mis;

};