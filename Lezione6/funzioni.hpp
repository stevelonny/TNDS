//#pragma once
#ifndef __funzioni_hpp__
#define __funzioni_hpp__

#include <iostream>
#include <cmath>

using namespace std;

class FunzioneBase{
    public:
        virtual double Eval(double x) const;
        virtual ~FunzioneBase();
};

class Parabola: public FunzioneBase{
    public:
        Parabola();
        Parabola(double a, double b, double c);
        Parabola(const Parabola &p);
        virtual ~Parabola();
        double Eval(double x) const override;
        
        void setA(double a);
        void setB(double b);
        void setC(double c);
        void set(double a, double b, double c);
        double getA() const;
        double getB() const;
        double getC() const;

    private:
        double m_a, m_b, m_c;
};

class x_Tanx : public FunzioneBase{
    public:
        x_Tanx();
        virtual ~x_Tanx();
        double Eval(double x) const override;
};

#endif //__funzioni_hpp__