#include "montecarlo.hpp"

MonteCarlo::MonteCarlo(unsigned int seed=1) : m_gen{seed}, m_punti{0} {}
MonteCarlo::~MonteCarlo() {}

double MonteCarlo::Media(const FunzioneBase &fun, double xmin, double xmax, unsigned int n_punti){
    double somma{0.};
    for(int i{0}; i<n_punti; i++){
        somma += fun.Eval(m_gen.Unif(xmin, xmax));
    }
    double media{(somma/(double)n_punti)*(xmax-xmin)};
    //cerr << somma << " " << media << endl;
    //m_errore = sqrt((1./((double)n_punti-1.))*(somma-(double)n_punti*media));
    m_punti = n_punti;
    m_mpunti = n_punti;
    return media;
}

double MonteCarlo::Hit(const FunzioneBase &fun, double xmin, double xmax, unsigned int n_punti, double ymax){
    double xrand{};
    double yrand{};
    m_mpunti = n_punti;
    m_punti = 0;
    for(int i{0}; i<n_punti; i++){
        xrand = m_gen.Unif(xmin, xmax);
        yrand = m_gen.Unif(0., ymax);
        if(yrand<=fun.Eval(xrand)){
            m_punti++;
        }
    }
    return ymax*((double)m_punti/((double)n_punti))*(xmax-xmin);
}

unsigned int MonteCarlo::GetN() const {
    return m_punti;
}

unsigned int MonteCarlo::GetMAX() const {
    return m_mpunti;
}