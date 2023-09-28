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
        //Funzione per la ricerca degli Zeri (max prec ca 1e-15)
        virtual double CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec = 1e-3, unsigned int nmax = 100);
        //Settare la precisione obiettivo (max ca 1e-15)
        void setPrecisione(double eps);
        //Settare num massimo di iterazioni
        void setNMaxIterations(unsigned int n);
        //Ottieni la precisione obiettivo
        double getPrecisione() const;
        //Ottieni num massimo di iterazioni
        unsigned int getNMaxIterations() const;
        //Ottieni num iterazioni attuali 
        unsigned int getNIterations() const;
        //Ottieni se valore trovato oppure no
        bool getFound() const;
        //Ottieni precisione reale
        double getRPrec();

    protected:
        //Aggiorna la precisione
        virtual void updateRPrec();
        //Ottieni il segno di un double
        double sign(double fx);
        double m_a, m_b; //Estremi della ricerca
        double m_prec; //Precisione richiesta
        unsigned int m_nmax, m_niterations; //Massime iterazioni e iterazioni attuali
        bool found; //Trovato oppure no il valore secondo la prec richiesta
        double r_prec; //Precisione reale
        double m_actual; //Valore trovato attuale
};
/* Metodo della Bisezione */
class Bisezione : public Solutore {
    public:
        Bisezione();
        Bisezione(double prec);
        virtual ~Bisezione();
        double CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec = 1e-3, unsigned int nmax = 100) override;
    private:
        double CercaZeri(const FunzioneBase & f);
};
/* Metodo della Secante */
class Secante : public Solutore{
    public:
        Secante();
        Secante(double prec);
        virtual ~Secante();
        double CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec = 1e-3, unsigned int nmax = 100) override;
    private:
        void updateRPrec() override; //calcolo diverso della precisione
        double CercaZeri(const FunzioneBase & f);
        double m_o; //utile solo per il metodo della Secante
};