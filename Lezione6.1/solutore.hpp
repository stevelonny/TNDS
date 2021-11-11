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
        double getRPrec();

    protected:
        virtual void updateRPrec();
        double sign(double fx);
        double m_a, m_b; //Estremi della ricerca
        double m_prec; //Precisione richiesta
        unsigned int m_nmax, m_niterations; //Massime iterazioni e iterazioni attuali
        bool found; //Trovato oppure no il valore secondo la prec richiesta
        double r_prec; //Precisione reale
        double m_actual; //Valore trovato attuale
};

class Bisezione : public Solutore {
    public:
        Bisezione();
        Bisezione(double prec);
        virtual ~Bisezione();
        double CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec = 1e-3, unsigned int nmax = 100) override;
    private:
        double CercaZeri(const FunzioneBase & f);
};

class Secante : public Solutore{
    public:
        Secante();
        Secante(double prec);
        virtual ~Secante();
        double CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec = 1e-3, unsigned int nmax = 100) override;
    private:
        void updateRPrec() override;
        double CercaZeri(const FunzioneBase & f);
        double m_o;
};