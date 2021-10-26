#ifndef __PuntoMateriale_h__
#define __PuntoMateriale_h__

#include "particella.hpp"
#include "posizione.hpp"

#include "campovettoriale.hpp"

class PuntoMateriale : public Particella, Posizione {
  public:
    //Costruttori e distruttore
    PuntoMateriale(double massa, double carica, const Posizione&);
    PuntoMateriale(double massa, double carica, double x, double y, double z);
    PuntoMateriale(const Particella& part, double x, double y, double z);
    PuntoMateriale(const Particella&, const Posizione&);
    ~PuntoMateriale();
    //Campi vari
    CampoVettoriale CampoElettrico(const Posizione&) const ;
    CampoVettoriale CampoGravitazionale(const Posizione&) const;
};

#endif // __PuntoMateriale_h__





