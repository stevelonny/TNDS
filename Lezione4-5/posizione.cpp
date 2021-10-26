#include "posizione.hpp"

Posizione::Posizione(){
    m_x = 0.;
    m_y = 0.;
    m_z = 0.;
}

Posizione::~Posizione(){}

Posizione::Posizione(double xp, double yp, double zp){
    m_x = xp;
    m_y = yp;
    m_z = zp;
}
//Cartesiane
double Posizione::getX() const {
    return m_x;
}
double Posizione::getY() const {
    return m_y;
}
double Posizione::getZ() const {
    return m_z;
}
//Sferiche
double Posizione::getR() const{
    return sqrt(m_x*m_x+m_y*m_y+m_z*m_z);
}
double Posizione::getPhi() const{
    return atan2(m_y,m_x);
}
double Posizione::getTheta() const{
    return acos(m_z/Posizione::getR());
}
//Rho delle cilindriche
double Posizione::getRho() const{
    return sqrt(m_x*m_x+m_y*m_y);
}
//Distanza
double Posizione::getDistance(const Posizione &pos) const{
    return sqrt(pow(m_x-pos.getX(), 2) + pow(m_y-pos.getY(), 2) + pow(m_z-pos.getZ(), 2));
}
double Posizione::getDistance(const double x, const double y, const double z) const{
    return sqrt(pow(m_x-x, 2) + pow(m_y-y, 2) + pow(m_z-z, 2));
}
//Distanza dall'origine
double Posizione::getDistance() const{
    return sqrt(pow(m_x, 2) + pow(m_x, 2) + pow(m_z, 2));
}
