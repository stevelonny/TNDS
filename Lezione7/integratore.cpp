#include "integratore.hpp"

/* Classe madre */
Integrale::Integrale() : m_a{}, m_b{}, m_sign{}, m_nstep{N_STEP}, m_h{} {}
Integrale::~Integrale(){};

double Integrale::Integrate(double a, double b, unsigned int nstep, FunzioneBase &f){
    m_nstep = nstep;
    checkInterval(a, b);
    return Calculate(f);
}

double Integrale::Calculate(FunzioneBase &f){
    return 0;
}

const double Integrale::getA(){
    return m_a;
}

const double Integrale::getB(){
    return m_b;
}

const double Integrale::getSign(){
    return m_sign;
}
const double Integrale::getH(){
    return m_h;
}
void Integrale::checkInterval(double a, double b){
    m_a = min(a, b);
    m_b = max(a, b);
    m_sign = (a < b) ? 1 :-1;
    m_h = (b-a)/m_nstep;
}

/* Classe midpoint */
Midpoint::Midpoint() : Integrale() {}
Midpoint::~Midpoint(){}

double Midpoint::Calculate(FunzioneBase &f){
    double sum{0};
    for(int i=0; i<m_nstep; i++){
        sum += f.Eval(getA()+(i+0.5)*getH());
    }
    return sum*getH()*getSign();
}

/* Simpson */
Simpson::Simpson() : Integrale(), r_nstep{} {}
Simpson::~Simpson() {}

void Simpson::checkInterval(double a, double b){
    r_nstep = (m_nstep%2==0?m_nstep:m_nstep+1); //Unica differenza da Integrale::checkInterval
    m_a = min(a, b);
    m_b = max(a, b);
    m_sign = (a < b) ? 1 :-1;
    m_h = (b-a)/r_nstep; //anche qua
}

double Simpson::Calculate(FunzioneBase &f){
    double sum = (1/3)*(f.Eval(getA())+f.Eval(getB()));
    for(int i=1; i<r_nstep; i++){
        sum += (((double)2)/((double)3))*(1+i%2)*(f.Eval(getA()+i*getH()));
        //cout << "[" << i << ":" << (2./3.) << "]";
    }
    //cout << "[" << sum << "]" << endl;
    return sum*getH();
}
