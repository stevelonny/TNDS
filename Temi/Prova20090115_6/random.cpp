#include "random.hpp"

RandomGen::RandomGen(unsigned int seed) : m_seed{seed}, m_m{1U << 31}, m_a{1664525}, m_c{1013904223} {}
RandomGen::RandomGen(unsigned int a, unsigned int c, unsigned int m, unsigned int seed) : m_a{a}, m_c{c}, m_m{m}, m_seed{seed} {}
void RandomGen::setA(unsigned int a) { m_a=a; }
void RandomGen::setC(unsigned int c) { m_c=c; }
void RandomGen::setM(unsigned int m) { m_m=m; }

double RandomGen::Rand(){
    m_seed = (m_a*m_seed+m_c)%m_m;
    return m_seed;
}

double RandomGen::Unif(double xmin=0., double xmax=1.){
    return xmin + (xmax-xmin)*(Rand()/m_m);
}

double RandomGen::Exp(double mean){
    return -mean*log(1-Unif());
}

double RandomGen::Gauss(double mean, double sigma){
    double s{Unif()};
    double t{Unif()};
    double x{sqrt(-2.*log(s))*cos(2.*M_PI*t)};
    return mean+x*sigma;
}

double RandomGen::GaussAR(double mean, double sigma){
    while(true){
        double x{Unif(-5.,5.)};
        double y{Unif()};
        double g{exp(-(x*x)/2.)};
        if(y<=g){
            return mean+x*sigma;
        }
    }
}

