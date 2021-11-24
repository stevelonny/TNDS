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



