#pragma once
#include "vettoriale.hpp"

class EquazioneDifferenzialeBase{
    public:
        EquazioneDifferenzialeBase();
        ~EquazioneDifferenzialeBase();
        virtual vector<double> Passo(double t, vector<double> stat, double h, FunzioneVettorialeBase &f);
};

class Eulero : public EquazioneDifferenzialeBase{
    public:
        Eulero();
        virtual ~Eulero();
        virtual vector<double> Passo(double t, vector<double> stat, double h, FunzioneVettorialeBase &f) override;
};