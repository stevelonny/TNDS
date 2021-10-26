#ifndef __campovettoriale_h__
#define __campovettoriale_h__

#include "posizione.hpp"

class CampoVettoriale : public Posizione {
  public:
    //Costruttori e distruttore
    CampoVettoriale(const Posizione&);
    CampoVettoriale(const Posizione&, double Fx, double Fy, double Fz);
    CampoVettoriale(double x, double y, double z, double Fx, double Fy, double Fz);
    ~CampoVettoriale();
    //Overloading di operatori
    CampoVettoriale & operator+=(const CampoVettoriale &) ;
    CampoVettoriale operator+(const CampoVettoriale &) const;
    //Resituisce i valori
    double getFx() const {return m_Fx;}
    double getFy() const {return m_Fy;}
    double getFz() const {return m_Fz;}
    //Restituisce il modulo
    double Modulo();
  private:
    double m_Fx, m_Fy, m_Fz;
};

#endif // __CampoVettoriale_h__ 


