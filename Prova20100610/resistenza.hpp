#pragma once
#include "random.hpp"
#include "iostream"
#include <vector>

using namespace std;

/* Funzioni di statistica base */
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

/* Classe simulazione resistenze */
class Resistenza {
    public:
        Resistenza() : R_in_m{59}, R1{90}, R2{10}, R3{50}, m_rand{1} {}
        ~Resistenza() {}

        void Esegui(){
            R1_m = m_rand.Gauss(R1, inc_r);
            R2_m = m_rand.Gauss(R2, inc_r);
            R3_m = m_rand.Gauss(R3, inc_r);
            calcolo();
        }
        vector<double> Analizza(unsigned int n_volte, vector<double> r_inc = {1, 3, 5, 7, 9}){
            vector<double> result;
            for(int i{0}; i<r_inc.size(); i++){
                inc_r = r_inc[i];
                vector<double> values;
                for(int j{0}; j<n_volte; j++){
                    cout << "Simulazione " << i+1 << "/" << r_inc.size() << ", con resistenza da " << r_inc[i] << "; istanza  " << j+1 << "/" << n_volte << "\r";
                    cout.flush();
                    Esegui();
                    values.push_back(R_in_m);
                }
                result.push_back(StdDev(values));
            }
            cout << endl;
            return result;
        }

    private:
        double R_in;
        double R_in_m;
        void calcolo() {
            R_in_m = (R1_m*R2_m+R2_m*R3_m+R3_m*R1_m) / (R1_m+R2_m);
        }
        double R1, R2, R3;
        double R1_m, R2_m, R3_m;
        double inc_in, inc_r;
        RandomGen m_rand;
};
