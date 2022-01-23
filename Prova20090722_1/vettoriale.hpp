#pragma once
#include "operator.hpp"
#include <cmath>

#define G_ (double)9.81

using namespace std;

class FunzioneVettorialeBase {
    public:
        FunzioneVettorialeBase() {}
        ~FunzioneVettorialeBase() {}
        virtual vector<double> Eval(vector<double> &pos, double t){
            vector<double> ciao{};
            return ciao;
        }
};

class ProtoneElettrico : public FunzioneVettorialeBase {
    public:
        ProtoneElettrico(double E0=1E8) : m_E0{E0}, m_k{1e-1}, m_omega{1E9}, m_mp{1.67e-27}, m_qp{1.60e-19} {}
        virtual ~ProtoneElettrico() {}
        virtual vector<double> Eval(vector<double> &pos, double t) override{
            return {pos[1], -1.*(m_qp/m_mp)*m_E0*sin(m_k*pos[0]-m_omega*t)}; 
        }
        void setE0(double E0){
            m_E0 = E0;
        }
    private:
        double m_E0;
        double m_k;
        double m_omega;
        double m_mp;
        double m_qp;

};