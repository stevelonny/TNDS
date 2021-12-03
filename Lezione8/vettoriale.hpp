#pragma once
#include "operator.hpp"
#include <cmath>

#define G_ (double)9.81

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

class Pendolo : public FunzioneVettorialeBase {
    public:
        Pendolo();
        Pendolo(double, double);
        virtual ~Pendolo();
        virtual vector<double> Eval(vector<double> &pos, double t) override;
        const double getLength();
        const double getG();
        void setLength(double l);
        void setG(double g);
    private:
        double m_g;
        double m_l;
};