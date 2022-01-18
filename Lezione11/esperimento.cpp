#include "esperimento.hpp"
#include <vector>

using namespace std;

EsperimentoPrisma::EsperimentoPrisma() :
    m_rand{1},
    m_inc{0.3e-3},
    m_lambda1{576.1e-9},
    m_lambda2{404.7e-9},
    m_alpha{60.*M_PI/180.},
    m_A{2.7},
    m_B{60000E-18},
    m_th0{M_PI/2.}
{
    m_n1 = sqrt(m_A + (m_B / (m_lambda1*m_lambda1)));
    m_n2 = sqrt(m_A + (m_B / (m_lambda2*m_lambda2)));
    fmt::print("Indici di partenza: n1 = {0:2.2f} , n2 = {1:2.2f}\n", m_n1, m_n2);
    m_dm1 = 2.*asinf32x(m_n1*sin(m_alpha/2.))-m_alpha;
    m_dm2 = 2.*asinf32x(m_n2*sin(m_alpha/2.))-m_alpha;
    fmt::print("Delta di partenza: delta_1 = {0:2.2f} , delta_2 = {1:2.2f}\n", m_dm1, m_dm2);
    m_th1 = m_th0 + m_dm1;
    m_th2 = m_th0 + m_dm2;
    fmt::print("Theta di partenza: theta_1 = {0:2.2f} , theta_2 = {0:2.2f}\n", m_th1, m_th2);
}

EsperimentoPrisma::~EsperimentoPrisma() {}

void EsperimentoPrisma::Esegui(){ 
    m_th0_mis = m_rand.Gauss(m_th0, m_inc);
    m_th1_mis = m_rand.Gauss(m_th1, m_inc);
    m_th2_mis = m_rand.Gauss(m_th2, m_inc);
    m_dm1_mis = m_th1_mis-m_th0_mis;
    m_dm2_mis = m_th2_mis-m_th0_mis;
    m_n1_mis = sin((m_dm1_mis+m_alpha)/2.)/sin(m_alpha/2.);
    m_n2_mis = sin((m_dm2_mis+m_alpha)/2.)/sin(m_alpha/2.);
    m_A_mis = (m_lambda2*m_lambda2*m_n2_mis*m_n2_mis-m_lambda1*m_lambda1*m_n1_mis*m_n1_mis) / (m_lambda2*m_lambda2-m_lambda1*m_lambda1);
    m_B_mis = (m_n2_mis*m_n2_mis-m_n1_mis*m_n1_mis) / (1./(m_lambda2*m_lambda2)-1./(m_lambda1*m_lambda1));
}

void EsperimentoPrisma::Analizza(unsigned int n_volte=10000){
    TCanvas can("sium", "sium", 1600, 900);
    vector<double> th0;
    vector<double> th1;
    vector<double> th2;
    vector<double> delta1;
    vector<double> delta2;
    vector<double> n1;
    vector<double> n2;
    vector<double> A;
    vector<double> B;
    for(int i{0}; i<n_volte; i++){
        Esegui();
        th0.push_back(m_th0_mis);
        th1.push_back(getTheta1Mis());
        th2.push_back(getTheta2Mis());
        delta1.push_back(getDelta1Mis());
        delta2.push_back(getDelta2Mis());
        n1.push_back(getn1Mis());
        n2.push_back(getn2Mis());
        A.push_back(getAMis());
        B.push_back(getBMis());
        cout << "Esperimento numero " << i+1 << "/" << n_volte << "\r";
        cout.flush();
    }
    std::cout << std::endl;

    TH1F histo_th0      = DoHisto("Theta 0", th0, n_volte);
    TH1F histo_th1      = DoHisto("Theta_1", th1, n_volte);
    TH1F histo_th2      = DoHisto("Theta_2", th2, n_volte);
    TH1F histo_delta1   = DoHisto("Delta_1", delta1, n_volte);
    TH1F histo_delta2   = DoHisto("Delta_2", delta2, n_volte);
    TH2F bhisto_delta   = DoBhisto("Delta", delta1, delta2, n_volte);
    TH1F histo_n1       = DoHisto("n1", n1, n_volte);
    TH1F histo_n2       = DoHisto("n2", n2, n_volte);
    TH2F bhisto_n       = DoBhisto("indici", n1, n2, n_volte); 
    TH1F histo_A        = DoHisto("A", A, n_volte);
    TH1F histo_B        = DoHisto("B", B, n_volte);
    TH2F bhisto_AB      = DoBhisto("AB", A, B, n_volte);
    histo_th0.StatOverflows(kTRUE);
    histo_th1.StatOverflows(kTRUE);
    histo_th2.StatOverflows(kTRUE);
    histo_delta1.StatOverflows(kTRUE);
    histo_delta2.StatOverflows(kTRUE);
    bhisto_delta.StatOverflows(kTRUE);
    histo_n1.StatOverflows(kTRUE);
    histo_n2.StatOverflows(kTRUE);
    bhisto_n.StatOverflows(kTRUE);
    histo_A.StatOverflows(kTRUE);
    histo_B.StatOverflows(kTRUE);
    bhisto_AB.StatOverflows(kTRUE);
    fmt::print("Stampiamo su file *.png i grafici...\n");
    can.Divide(3,1);
    can.cd(1);
    histo_th0.Draw();
    can.cd(2);
    histo_th1.Draw();
    can.cd(3);
    histo_th2.Draw();
    can.Print("theta.png");
    can.Clear("D");
    can.cd(1);
    histo_delta1.Draw();
    can.cd(2);
    histo_delta2.Draw();
    can.cd(3);
    bhisto_delta.Draw();
    can.Print("delta.png");
    can.Clear("D");
    can.cd(1);
    histo_n1.Draw();
    can.cd(2);
    histo_n2.Draw();
    can.cd(3);
    bhisto_n.Draw();
    can.Print("indici.png");
    can.Clear("D");
    can.cd(1);
    histo_A.Draw();
    can.cd(2);
    histo_B.Draw();
    can.cd(3);
    bhisto_AB.Draw();
    can.Print("AB.png");
    can.Clear("D");
    vector<string> value_names{"th0", "th1", "th2", "delta1", "delta2", "n1", "n2", "A", "B"};
    fmt::print("Correlazione delta:      {0:2.0f}%\n", bhisto_delta.GetCorrelationFactor()*100);
    fmt::print("Correlazione indici:     {0:2.0f}%\n", bhisto_n.GetCorrelationFactor()*100);
    fmt::print("Correlazione AB:        {0:2.0f}%\n", bhisto_AB.GetCorrelationFactor()*100);

    fmt::print("Terminato!\n");
}

TH1F EsperimentoPrisma::DoHisto(const char* name, vector<double> &values, int n_volte){
    TH1F histo(name, name, 100, *min_element(values.begin(), values.end()), *max_element(values.begin(), values.end()));
    for(int i{0}; i<n_volte; i++){
        histo.Fill(values[i]);
    }
    return histo;
}

TH2F EsperimentoPrisma::DoBhisto(const char* name, vector<double> &xvalues, vector<double> &yvalues, int n_volte){
    TH2F bhisto(name, name, 100, *min_element(xvalues.begin(), xvalues.end()), *max_element(yvalues.begin(), yvalues.end()), 100, *min_element(yvalues.begin(), yvalues.end()), *max_element(yvalues.begin(), yvalues.end()));
    for(int i{0}; i<n_volte; i++){
        bhisto.Fill(xvalues[i], yvalues[i]);
    }
    return bhisto;
}
