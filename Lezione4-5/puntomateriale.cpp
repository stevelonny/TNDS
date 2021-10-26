#include "puntomateriale.hpp"
#define eps0 (double)8.85418781762E-12
#define G (double)6.67430E-11
//Costruttori e distruttore
PuntoMateriale::PuntoMateriale(double massa, double carica, const Posizione& pos)
    : Particella(massa, carica), Posizione(pos) {}
PuntoMateriale::PuntoMateriale(double massa, double carica, double x, double y, double z)
    : Particella(massa, carica), Posizione(x, y, z){}
PuntoMateriale::PuntoMateriale(const Particella& part, double x, double y, double z)
    : Particella(part), Posizione(x, y, z){}
PuntoMateriale::PuntoMateriale(const Particella& part, const Posizione& pos)
    : Particella(part), Posizione(pos){}
PuntoMateriale::~PuntoMateriale(){}
/* Campo Elettrico */
CampoVettoriale PuntoMateriale::CampoElettrico(const Posizione& pos) const {
    //Calcoliamo costante k e raggio
    double k = m_carica/(4*M_PI*eps0*pow(getDistance(pos), 3));
    //Per componenti cartesiane
    double E_x = k*(pos.getX()-getX());
    double E_y = k*(pos.getY()-getY());
    double E_z = k*(pos.getZ()-getZ());
    //Restituiamo il campo generato nel punto pos
    return CampoVettoriale(pos, E_x, E_y, E_z);
}
/* Campo Gravitazionale */
CampoVettoriale PuntoMateriale::CampoGravitazionale(const Posizione& pos) const {
    //Calcoliamo la parte costante
    double k = m_massa*G/pow(getDistance(pos), 3);
    //Per componenti cartesiane
    double Fg_x = k*(+pos.getX()-getX());
    double Fg_y = k*(+pos.getY()-getY());
    double Fg_z = k*(+pos.getZ()-getZ());
    //Restituiamo il campo generato nel punto pos
    return CampoVettoriale(pos, Fg_x, Fg_y, Fg_z);
}