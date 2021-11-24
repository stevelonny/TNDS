#pragma once
#include "operator.hpp"
#include <cmath>

using namespace std;

class FunzioneVettorialeBase {
    public:
        FunzioneVettorialeBase();
        ~FunzioneVettorialeBase();
        virtual vector<double> Eval(vector<double> &pos, double t);

};

class OscillatoreArmonicoSemplice : public FunzioneVettorialeBase {
    public:
            OscillatoreArmonicoSemplice();
            OscillatoreArmonicoSemplice(double om);
            virtual ~OscillatoreArmonicoSemplice();
            virtual vector<double> Eval(vector<double> &pos, double t) override;
            const double getOmega();
            void setOmega(double om);
    private:
         double m_omega;
         //double m_t0;
         //vector<double> vett0;
};

 