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
    std::cout << m_n1 << " " << m_n2 << std::endl;
    m_dm1 = 2.*asinf32x(m_n1*sin(m_alpha/2.))-m_alpha;
    m_dm2 = 2.*asinf32x(m_n2*sin(m_alpha/2.))-m_alpha;
    std::cout << m_dm1 << " " << m_dm2 << std::endl;
    m_th1 = m_th0 + m_dm1;
    m_th2 = m_th0 + m_dm2;
    cout << m_th1 << " " << m_th2 << endl;
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

    TH1F histo_th0("Theta_0", "Theta_0", 100, *min_element(th0.begin(), th0.end()), *max_element(th0.begin(), th0.end()));
    TH1F histo_th1("Theta_1", "Theta_1", 100, *min_element(th1.begin(), th1.end()), *max_element(th1.begin(), th1.end()));
    TH1F histo_th2("Theta_2", "Theta_2", 100, *min_element(th2.begin(), th2.end()), *max_element(th2.begin(), th2.end()));
    TH1F histo_delta1("Delta_1", "Delta_1", 100, *min_element(delta1.begin(), delta1.end()), *max_element(delta1.begin(), delta1.end()));
    TH1F histo_delta2("Delta_2", "Delta_2", 100, *min_element(delta2.begin(), delta2.end()), *max_element(delta2.begin(), delta2.end()));
    TH2F bhisto_delta("Delta", "Delta", 100, *min_element(delta1.begin(), delta1.end()), *max_element(delta1.begin(), delta1.end()), 100, *min_element(delta2.begin(), delta2.end()), *max_element(delta2.begin(), delta2.end()));
    TH1F histo_n1("n1", "n1", 100, *min_element(n1.begin(), n1.end()), *max_element(n1.begin(), n1.end()));
    TH1F histo_n2("n2", "n2", 100, *min_element(n2.begin(), n2.end()), *max_element(n2.begin(), n2.end()));
    TH2F bhisto_n("n", "n", 100, *min_element(n1.begin(), n1.end()), *max_element(n1.begin(), n1.end()), 100, *min_element(n2.begin(), n2.end()), *max_element(n2.begin(), n2.end()));
    TH1F histo_A("A", "A", 100, *min_element(A.begin(), A.end()), *max_element(A.begin(), A.end()));
    TH1F histo_B("B", "B", 100, *min_element(B.begin(), B.end()), *max_element(B.begin(), B.end()));
    TH2F bhisto_AB("AB", "AB", 100, *min_element(A.begin(), A.end()), *max_element(A.begin(), A.end()), 100, *min_element(B.begin(), B.end()), *max_element(B.begin(), B.end()));
    for(int i{0}; i<n_volte; i++){
        histo_th0.Fill(th0[i]);
        histo_th1.Fill(th1[i]);
        histo_th2.Fill(th2[i]);
        histo_delta1.Fill(delta1[i]);
        histo_delta2.Fill(delta2[i]);
        bhisto_delta.Fill(delta1[i], delta2[i]);
        histo_n1.Fill(n1[i]);
        histo_n2.Fill(n2[i]);
        bhisto_n.Fill(n1[i], n2[i]);
        histo_A.Fill(A[i]);
        histo_B.Fill(B[i]);
        bhisto_AB.Fill(A[i], B[i]);
    }
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
