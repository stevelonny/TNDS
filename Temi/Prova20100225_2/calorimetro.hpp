
#include "random.hpp"
#include <vector>
#include <iostream>

using namespace std;

//Media
template <typename T> double Mean(const vector<T> & vett){ //teniamo double che è meglio
    T mean;
    T sum = 0;
    
    for(int i=0; i<vett.size(); i++){
        sum+=vett[i];
    }
    mean = sum/(double)vett.size();

    return mean;
}
//Deviazione standard
template <typename T> double StdDev(const vector<T> &data){
    double dev;
    double sum=0;
    double mean=Mean(data);

    for(int i=0; i<data.size(); i++){
        sum+=pow((data[i]-mean), 2);
    }
    dev = sqrt(sum/(double)data.size());

    return dev;
}

class EsperimentoCalorimetro {
    public:
        EsperimentoCalorimetro() : 
        m_a{150.}, inc_ma{2.}, T_a{16.1}, inc_Ta{0.2}, m_c{27.737}, T_c{90.6}, inc_Tc{0.4}, T_e{17.2}, inc_Te{0.2},
        m_ast{25.}, inc_mast{5.}, m_rand(1.), c_a{1.} {}
        ~EsperimentoCalorimetro() {}

        double getCalMis(){return c_0_mis;}
        double getMean(){return mean;}
        double getStd(){return std;}
        double getIncMa(){return inc_ma;}
        double getIncMast(){return inc_mast;}
        double getIncTa(){return inc_Ta;}
        double getIncTe(){return inc_Te;}
        double getIncTc(){return inc_Tc;}
        
        void setIncMa(double inc){inc_ma = inc;}
        void setIncMast(double inc){inc_mast = inc;}
        void setIncTa(double inc){inc_Ta = inc;}
        void setIncTe(double inc){inc_Te = inc;}
        void setIncTc(double inc){inc_Tc = inc;}
        
        void Analizza(unsigned int n_volte){
            vector<double> calori;
            for(int i{0}; i<n_volte; i++){
                cout << "Esperimento numero " << i+1 << "/" << n_volte << "\r";
                cout.flush();
                Esegui();
                calori.push_back(getCalMis());
            }
            cout << endl;
            mean = Mean(calori);
            std = StdDev(calori);
        }

    private:
        double mean, std;
        void Esegui(){
            m_a_mis     = m_rand.Gauss(m_a, inc_ma);
            m_ast_mis   = m_rand.Gauss(m_ast, inc_mast);
            T_a_mis     = m_rand.Gauss(T_a, inc_Ta);
            T_e_mis     = m_rand.Gauss(T_e, inc_Te);
            T_c_mis     = m_rand.Gauss(T_c, inc_Tc);
            c_0_mis     = CaloreSpecificoMis();
        }
        double m_a, m_c, m_ast;
        double inc_ma, inc_mast;
        double T_a, T_c, T_e;
        double inc_Ta, inc_Tc, inc_Te;
        double c_a;
        double c_0;
        RandomGen m_rand;
        double m_a_mis, m_ast_mis;
        double T_a_mis, T_c_mis, T_e_mis;
        double c_0_mis;
        double CaloreSpecificoMis(){
            return ((m_a_mis+m_ast_mis)*c_a*(T_e_mis-T_a_mis))/(m_c*(T_c_mis-T_e_mis));
        }
};