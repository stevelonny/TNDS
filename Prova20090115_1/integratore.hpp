#pragma once

#include "funzioni.hpp"

#define N_STEP (int)100
#define M_PREC (double)1e-3

using namespace std;

class Integrale{
    public:
        Integrale();
        virtual ~Integrale();
        virtual double Integrate(double a, double b, unsigned int nstep, FunzioneBase &f);
        const double getA();
        const double getB();
        const double getSign();
        const double getH();
    protected:
        unsigned int m_nstep;
        double m_h;
        double m_a, m_b; //Estremi di integrazione
        double m_sign;   //Segno
        virtual void checkInterval(double a, double b);
    private:
        virtual double Calculate(FunzioneBase &f);
        
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

class Trapezoidi : public Integrale{
    public:
        Trapezoidi();
        virtual ~Trapezoidi();
        double Integrate(double a, double b, double prec, FunzioneBase &f);
        void setPrecision(double prec);
        double getPrecision();
        int getIterations();

    private:
        double Calculate(FunzioneBase &f) override;
        double CalculatePrec(FunzioneBase &f);
        double m_prec, r_prec;
        unsigned int m_iterations;
};