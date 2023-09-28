#pragma once

#include <cmath>

class RandomGen {
    public:
        RandomGen(unsigned int seed);
        RandomGen(unsigned int a, unsigned int c, unsigned int m, unsigned int seed);
        void setA(unsigned int a);
        void setC(unsigned int c);
        void setM(unsigned int m);

        double Rand();
        double Unif(double xmin, double xmax);
        double Exp(double mean);
        double Gauss(double mean, double sigma);
        double GaussAR(double mean, double sigma);
    private:
        unsigned int m_a, m_c, m_m;
        unsigned int m_seed;
};