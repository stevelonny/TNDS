#include "vettoriale.hpp"

/* Funzione Vettorial Base */

FunzioneVettorialeBase::FunzioneVettorialeBase(){}
FunzioneVettorialeBase::~FunzioneVettorialeBase(){}
vector<double> FunzioneVettorialeBase::Eval(vector<double> &pos, double t){
    vector<double> ciao{};
    return ciao;
}

/* Oscillatore Armonico Semplice */

OscillatoreArmonicoSemplice::OscillatoreArmonicoSemplice() : m_omega{1} {}
OscillatoreArmonicoSemplice::OscillatoreArmonicoSemplice(double om) : m_omega{om} {}
OscillatoreArmonicoSemplice::~OscillatoreArmonicoSemplice() {}
const double OscillatoreArmonicoSemplice::getOmega(){
    return m_omega;
}
void OscillatoreArmonicoSemplice::setOmega(double om){
    m_omega = om;
}
vector<double> OscillatoreArmonicoSemplice::Eval(vector<double> &pos, double t){
    int dim = pos.size()/2;
    vector<double> result(pos.size());
    for(int i=0; i<pos.size(); i++){
        if(i<dim){
            result[i]=pos[i+dim];
        }
        else{
            result[i]=pos[i-dim]*(-(getOmega()*getOmega()));
        }
    }
    return result;
}

/* Pendolo */

Pendolo::Pendolo() : m_g{G_}, m_l{1} {}
Pendolo::Pendolo(double l, double g=G_) : m_g{g}, m_l{l} {}
Pendolo::~Pendolo() {}

const double Pendolo::getG(){return m_g;}
const double Pendolo::getLength(){return m_l;}
void Pendolo::setG(double g){m_g = g;}
void Pendolo::setLength(double l){m_l = l;}

vector<double> Pendolo::Eval(vector<double> &pos, double t){
    vector<double> result(2);
    result = {pos[1], (-(getG()/getLength()))*sin(pos[0])};
    return result;
}

/* Oscilatore armonico forzato e pure smorzato */

OscillatoreArmonicoForzato::OscillatoreArmonicoForzato() {}
OscillatoreArmonicoForzato::OscillatoreArmonicoForzato(double omega_0, double alpha, double omega) : m_omega0{omega_0}, m_omega{omega}, m_alpha{alpha} {}
OscillatoreArmonicoForzato::~OscillatoreArmonicoForzato() {}

const double OscillatoreArmonicoForzato::getOmega0(){return m_omega0;}
const double OscillatoreArmonicoForzato::getOmega(){return m_omega;}
const double OscillatoreArmonicoForzato::getAlpha(){return m_alpha;}
void OscillatoreArmonicoForzato::setOmega0(double omega0){m_omega0 = omega0;}
void OscillatoreArmonicoForzato::setOmega(double omega){m_omega = omega;}
void OscillatoreArmonicoForzato::setAlpha(double alpha){m_alpha = alpha;}

vector<double> OscillatoreArmonicoForzato::Eval(vector<double> &pos, double t){
    int dim = pos.size()/2;
    vector<double> result(pos.size());
    /* for(int i=0; i<pos.size(); i++){
        if(i<dim){
            result[i]=pos[i+dim];
        }
        else{
            result[i]=pos[i-dim]*(-(getOmega0()*getOmega0()))-pos[i]*getAlpha()+sin(getOmega()*t);
        }
    } */
    result[0] = pos[1];
    result[1] = pos[0]*(-(getOmega0()*getOmega0()))-pos[1]*getAlpha()+sin(getOmega()*t);
    return result;
}
