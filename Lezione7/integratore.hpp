#pragma once

#include "funzioni.hpp"

#define N_STEP (int)100

using namespace std;

class Integrale{
    public:
        Integrale();
        virtual ~Integrale();
        double Integrate(double a, double b, unsigned int nstep, FunzioneBase &f);
        const double getA();
        const double getB();
        const double getSign();
        const double getH();
    protected:
        unsigned int m_nstep;
        double m_h;
        double m_a, m_b; //Estremi di integrazione
        double m_sign;   //Segno
    private:
        virtual double Calculate(FunzioneBase &f);
        virtual void checkInterval(double a, double b);
        
};

class Midpoint : public Integrale{
    public:
        Midpoint();
        virtual ~Midpoint();

    private:
        double Calculate(FunzioneBase &f) override;

};

class Simpson : public Integrale{
    public: 
        Simpson();
        virtual ~Simpson();
    
    private:
        double Calculate(FunzioneBase &f) override;
        void checkInterval(double a, double b) override;
        unsigned int r_nstep;
};