#include "campovettoriale.hpp"
//Costruttore e distruttore
CampoVettoriale::CampoVettoriale(const Posizione& pos) : Posizione(pos){
    m_Fx = 0.;
    m_Fy = 0.;
    m_Fz = 0.;
}
CampoVettoriale::CampoVettoriale(const Posizione& pos, double Fx, double Fy, double Fz) : Posizione(pos) {
    m_Fx = Fx;
    m_Fy = Fy;
    m_Fz = Fz;
}
CampoVettoriale::CampoVettoriale(double x, double y, double z, double Fx, double Fy, double Fz) : Posizione(x, y, z){
    m_Fx = Fx;
    m_Fy = Fy;
    m_Fz = Fz;
}
CampoVettoriale::~CampoVettoriale(){}
//Operatori
CampoVettoriale CampoVettoriale::operator+(const CampoVettoriale & v) const{
    CampoVettoriale sum(v);
    sum.m_Fx += m_Fx;
    sum.m_Fy += m_Fy;
    sum.m_Fz += m_Fz;
    return sum;
}
CampoVettoriale & CampoVettoriale::operator+=(const CampoVettoriale & v){
    return (*this) = (*this)+v;
}
//Modulo
double CampoVettoriale::Modulo(){
    return sqrt(m_Fx*m_Fx+m_Fy*m_Fy+m_Fz*m_Fz);
}
