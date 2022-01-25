#pragma once

#include "funzioni.hpp"
#include "random.hpp"

class MonteCarlo {
    public:
        MonteCarlo(unsigned int seed);
        ~MonteCarlo();

        double Media(const FunzioneBase &fun, double xmin, double xmax, unsigned int n_punti);
        double Hit(const FunzioneBase &fun, double xmin, double xmax, unsigned int n_punti, double ymax);
        unsigned int GetN() const;
        unsigned int GetMAX() const;

    private:
        RandomGen m_gen;
        unsigned int m_punti;
        unsigned int m_mpunti;
};