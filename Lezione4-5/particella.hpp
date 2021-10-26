#ifndef __particella_h__
#define __particella_h__
#include <iostream>
#include <cmath>

using namespace std;

class Particella{
    public:
        //Costruttori
        Particella();
        Particella(double massa, double carica);
        //Distruttore
        ~Particella();
        //Restituisce i valori
        double getMassa() const;
        double getCarica() const;
        //Stampa valori
        void Print() const;
    protected:
        double m_massa;
        double m_carica;
};

class Elettrone : public Particella{
    public:
        //Costruttore e distruttore
        Elettrone();
        ~Elettrone();
        //Stampa
        void Print() const;
};

class Protone : public Particella{
    public:
        //Costruttore e distruttore
        Protone();
        ~Protone();
        //Stampa
        void Print() const;
};

#endif