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
    double sum = (f.Eval(getA())+f.Eval(getB()));
    for(int i=1; i<r_nstep; i++){
        sum += (2.)*(1+i%2)*(f.Eval(getA()+i*getH()));
    }
    return sum*getH()*(1./3.)*getSign();
}

/* Trapezoidi */

Trapezoidi::Trapezoidi() : Integrale(), m_iterations{0}, m_prec{M_PREC}, r_prec{} {}
Trapezoidi::~Trapezoidi() {}


void Trapezoidi::setPrecision(double prec){
    m_prec = prec;
}

double Trapezoidi::getPrecision(){
    return r_prec;
}

int Trapezoidi::getIterations(){
    return m_iterations;
}

double Trapezoidi::Integrate(double a, double b, double prec, FunzioneBase &f){
    //cout << "Trap Int" << endl;
    m_nstep = 2;
    checkInterval(a, b);
    setPrecision(prec);
    return CalculatePrec(f);
}

double Trapezoidi::CalculatePrec(FunzioneBase &f){
    m_iterations = 0;
    double oldint{Calculate(f)};
    double newint{oldint};
    //cout << r_prec << " " << m_prec << endl;
    while(true){
        oldint = newint;
        m_nstep *= 2.;
        m_h /= 2.;
        newint = Calculate(f);
        m_iterations = m_nstep;
        r_prec = ((double)4/(double)3)*fabs(newint-oldint);
        //cout << oldint << " " << newint << endl;
        if(r_prec<=m_prec){
            break;
        }
    }
    return  newint;
}

double Trapezoidi::Calculate(FunzioneBase &f){
    double sum = (f.Eval(getA())+f.Eval(getB()))*0.5;
    for(int i=1; i<m_nstep; i++){
        sum += f.Eval(getA()+(double)i*getH());
    }
    return sum*getH()*getSign();
}