#include "funzioni.hpp"

double FunzioneBase::Eval(double x) const {return 0;}
FunzioneBase::~FunzioneBase(){};


/* Parabola */
Parabola::Parabola() {}
Parabola::Parabola(double a, double b, double c) : m_a{a}, m_b{b}, m_c{c} {}
Parabola::Parabola(const Parabola &p) :  m_a{p.getA()}, m_b{p.getB()}, m_c{p.getC()} {}
Parabola::~Parabola() {}

double Parabola::Eval(double x) const{
    return getA()*pow(x, 2) + getB()*x + getC();
}

void Parabola::setA(double a) {m_a = a;}
void Parabola::setB(double b) {m_b = b;}
void Parabola::setC(double c) {m_c = c;}
void Parabola::set(double a, double b, double c) {
    m_a = a;
    m_b = b;
    m_a = c;
}
double Parabola::getA() const {return m_a;}
double Parabola::getB() const {return m_b;}
double Parabola::getC() const {return m_c;}

/* x_Tanx ovvero x-tan(x)*/
x_Tanx::x_Tanx() {}
x_Tanx::~x_Tanx() {} 
 
double x_Tanx::Eval(double x) const{
    return /* x-tan(x) */ sin(x)-x*cos(x);
}
