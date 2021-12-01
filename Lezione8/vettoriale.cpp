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

const double Pendolo::getG(){ return m_g;}
const double Pendolo::getLength(){return m_l;}
void Pendolo::setG(double g){m_g = g;}
void Pendolo::setLength(double l){m_l = l;}

vector<double> Pendolo::Eval(vector<double> &pos, double t){
    int dim = pos.size()/2;
    vector<double> result(pos.size());
    for(int i=0; i<pos.size(); i++){
        if(i<dim){
            result[i]=pos[i+dim];
        }
        else{
            result[i]=(-(getG()/getLength()))*sin(pos[i-dim]);
        }
    }
    return result;
}

