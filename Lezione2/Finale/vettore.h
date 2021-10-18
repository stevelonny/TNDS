#ifndef __Vettore__
#define __Vettore__
#include <iostream>


class Vettore {
    public:
        
        Vettore();
        Vettore(unsigned int dim);
        ~Vettore();
        Vettore(const Vettore &vett);

        unsigned int GetN() const;
        void SetComponent(unsigned int k, double val);
        double GetComponent(unsigned int k) const;
        void Scambia(unsigned int k, unsigned int j);
        
        double & operator[](unsigned int index);
        Vettore & operator=(const Vettore &vett);
        Vettore(const Vettore &&vett);

    private:
        unsigned int m_N;
        double * m_V;
};




#endif