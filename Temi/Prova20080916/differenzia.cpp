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

/* Metodo di Runge-Kutta */
Kutta::Kutta() {}
Kutta::~Kutta() {}
vector<double> Kutta::Passo(double t, vector<double> stat, double h, FunzioneVettorialeBase &f){
    vector<double> k1{f.Eval(stat, t)};
    vector<double> tempstat{stat+k1*(h/2.)};
    vector<double> k2{f.Eval(tempstat, t+(h/2.))};
    tempstat = stat+k2*(h/2.);
    vector<double> k3{f.Eval(tempstat, t+(h/2.))};
    tempstat = stat+k3*h;
    vector<double> k4{f.Eval(tempstat, t+h)};
    return stat+(k1+k2*2.+k3*2.+k4)*(h/6.);
}