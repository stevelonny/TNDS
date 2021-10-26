#ifndef __posizione_h__
#define __posizione_h__
#include <iostream>
#include <cmath>

using namespace std;

class Posizione {
    public :
        //Costruttori
        Posizione();
        Posizione(double xp, double yp, double zp);
        //Posizione(const Posizione &pos);
        //Distruttore
        ~Posizione();
        //Restituisce coordinate cartesiane
        double getX() const;
        double getY() const;
        double getZ() const;
        //Restituisce coordinate sferiche
        double getR() const;
        double getPhi() const;
        double getTheta() const;
        //Restituisce coordinate cilindriche (serve solo Rho)
        double getRho() const;
        //Distanza
        double getDistance(const Posizione &pos) const;
        double getDistance(const double x, const double y, const double z) const;
        double getDistance() const;
        //Operatori & Co.
        //double & operator[](unsigned int index);
        //Posizione & operator=(Posizione &&vett);
        //Posizione(Posizione &&vett);

    private :
        double m_x, m_y, m_z;
};

#endif