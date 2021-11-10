#pragma once
//#ifndef __solutore_hpp__
//#define __solutore_hpp__

#include "funzioni.hpp"

#define M_PREC 1e-3
#define N_MAX 100

using namespace std;

class Solutore{
    public:
        Solutore();
        virtual ~Solutore();

        virtual double CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec = 1e-3, unsigned int nmax = 100);
        void setPrecisione(double eps);
        void setNMaxIterations(unsigned int n);
        double getPrecisione() const;
        unsigned int getNMaxIterations() const;
        unsigned int getNIterations() const;
        bool getFound() const;

    protected:
        double m_a, m_b;
        double m_prec;
        unsigned int m_nmax, m_niterations;
        bool found;
};

class Bisezione : public Solutore {
    public:
        Bisezione();
        Bisezione(double prec);
        virtual ~Bisezione();
        double CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec = 1e-3, unsigned int nmax = 100) override;
};

class Secante : public Solutore{
    public:
        Secante();
        Secante(double prec);
        virtual ~Secante();
        double CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec = 1e-3, unsigned int nmax = 100) override;
};

//#endif //__solutore_hpp__