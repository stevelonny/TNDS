#include "differenzia.hpp"

/* Equazione Differenziale Base */
EquazioneDifferenzialeBase::EquazioneDifferenzialeBase() {}
EquazioneDifferenzialeBase::~EquazioneDifferenzialeBase() {}
vector<double> EquazioneDifferenzialeBase::Passo(double t, vector<double> stat, double h, FunzioneVettorialeBase &f){
    return vector<double>{};
}

/* Metodo di Eulero */
Eulero::Eulero() {}
Eulero::~Eulero() {}
vector<double> Eulero::Passo(double t, vector<double> stat, double h, FunzioneVettorialeBase &f){
    return operator+(stat, operator*(h, f.Eval(stat, t)));    
}