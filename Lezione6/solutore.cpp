#include "solutore.hpp"

double sign(double x);

/* Metodi Solutore */
Solutore::Solutore() : found{false} {}
Solutore::~Solutore(){}
double Solutore::CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec /* = 1e-3 */, unsigned int nmax /* = 100 */){
    found = false;
    return 0;
}
bool Solutore::getFound() const{
    return found;
}
/* double Solutore::CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec = 1e-3, unsigned int nmax = 100){
    return 0;
} */
void Solutore::setPrecisione(double eps){
    m_prec = eps;
}
void Solutore::setNMaxIterations(unsigned int nmax){
    m_nmax = nmax;
}
double Solutore::getPrecisione() const {
    return m_prec;
}
unsigned int Solutore::getNMaxIterations() const {
    return m_nmax;
}
unsigned int Solutore::getNIterations() const {
    return m_niterations;
}

/* Metodi della bisezione */
Bisezione::Bisezione(){
    found = false;
    m_niterations = 0;
}
Bisezione::Bisezione(double prec) {
    found = false;
    m_niterations = 0;
    m_prec = prec;
}
Bisezione::~Bisezione(){}
double Bisezione::CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec /* = 1e-3 */, unsigned int nmax /* = 100 */){
    /* Passaggio 0 */
    //Impostiamo i parametri di ricerca
    m_prec = prec;
    m_nmax = nmax;
    //Impostiamo gli estremi di ricerca
    m_a = xmin;
    m_b = xmax;
    //Calcolo la mediana tra dell'intervallo [m_a,m_b]
    double med = (m_a+m_b)*0.5;
    //Ottengo il segno degli estremi e della mediana
    double sign_a{sign(f.Eval(m_a))};
    //cerr << " " << sign_a << " ";
    double sign_b{sign(f.Eval(m_b))};
    //cerr << " " << sign_b << " ";
    double sign_med{sign(f.Eval(med))};
    //cerr << " " << sign_med << " ";
    //Controlliamo che gli estremi o la mediana non siano già lo zero della funzione
    if(sign_a==0||sign_b==0){
        found = true;
        return (sign_a == 0 ? m_a : m_b);
    }
    else if(sign_med==0){
        m_niterations++;
        if(m_niterations>=m_nmax){
            found = false;
            return nan("");
        }
        found = true;
        return med;
    }
    else if(sign_a*sign_b>0){
        found = false;
        return nan("");
    }
    /* Passaggio sium */
    while(fabs(m_a-m_b)>=m_prec){
        if(sign_a*sign_med<0){ //Se sta a sx richiamiamo CercaZeri sull'intorno [m_a,med]
            m_niterations++;
            if(m_niterations>=m_nmax){//Controllo se non ha finito i tentativi
                found = false;
                return med;
            }
            return Bisezione::CercaZeriReference(m_a, med, f, prec, nmax);
        }
        else if(sign_med*sign_b<0){ //Se sta a dx richiamiamo CercaZeri sull'intorno [med,m_b]
            m_niterations++;
            if(m_niterations>=m_nmax){ //Controllo se non ha finito i tentativi
                found = false;
                return med;
            }
            return Bisezione::CercaZeriReference(med, m_b, f, prec, nmax);
        }
    }
    found = true;
    return (fabs(m_a-m_b)<m_prec ? med : nan(""));
}

double sign(double x){
    return x != 0 ? copysign(1.0, x) : 0.0; 
}