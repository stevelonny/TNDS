#include "particella.hpp"
/*Particella*/
//Costruttori
Particella::Particella(){
    m_massa = 0.;
    m_carica = 0.;
}
Particella::Particella(double massa, double carica){
    m_massa = massa;
    m_carica = carica;
}
//Distruttore
Particella::~Particella(){}
//Ottieni valori
double Particella::getMassa() const{
    return m_massa;
}
double Particella::getCarica() const{
    return m_carica;
}
//Stampa
void Particella::Print() const{
    cout << "Particella - massa: " << m_massa << " carica: " << m_carica << endl;
}
/*Elettrone*/
//Costruttore
Elettrone::Elettrone() : Particella(9.1093826E-31,-1.60217653E-19){}
Elettrone::~Elettrone(){}
//Stampa
void Elettrone::Print() const{
    cout << "Elettrone - massa: " << m_massa << " carica: " << m_carica << endl;
}
/*Protone*/
//Costruttore
Protone::Protone() : Particella(1.67262171E-27,1.60217653E-19){}
Protone::~Protone(){}
//Stampa
void Protone::Print() const{
    cout << "Protone - massa: " << m_massa << " carica: " << m_carica << endl;
}