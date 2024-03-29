#include "solutore.hpp"

double sign(double x);

/* Metodi Solutore */
Solutore::Solutore() : found{false}, m_nmax{N_MAX}, m_prec{M_PREC}, r_prec{nan("")} {}
Solutore::~Solutore(){}
double Solutore::CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec /* = 1e-3 */, unsigned int nmax /* = 100 */){
    m_prec = (m_prec == M_PREC ? prec : m_prec) ;
    m_nmax = (m_nmax == N_MAX ? nmax : m_nmax);
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
void Solutore::updateRPrec(){
    r_prec = (isnan(fabs(m_a-m_b))?0:fabs(m_a-m_b));
}
double Solutore::getRPrec(){
    return r_prec;
}

/* Metodi della bisezione */
Bisezione::Bisezione(){
    found = false;
    m_niterations = 0;
    m_prec = M_PREC;
    m_nmax = N_MAX;
    r_prec = nan("");
}
Bisezione::Bisezione(double prec) {
    found = false;
    m_niterations = 0;
    m_prec = prec;
    m_nmax = N_MAX;
    r_prec = nan("");
}
Bisezione::~Bisezione(){}
double Bisezione::CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec /* = 1e-3 */, unsigned int nmax /* = 100 */){
    //cerr << " " << m_niterations << " ";
    if(found==true||m_niterations>=m_nmax){
        //Puliamo il solutore
        m_niterations = 0;
        found = false;
    }
    updateRPrec();
    /* Passaggio 0 */
    //Impostiamo i parametri di ricerca
    m_prec = (m_prec == M_PREC ? prec : m_prec);
    m_nmax = (m_nmax == N_MAX ? nmax : m_nmax);
    //Impostiamo gli estremi di ricerca
    m_a = xmin;
    m_b = xmax;
    //Calcolo la mediana tra dell'intervallo [m_a,m_b]
    double med = (m_a+m_b)*0.5;
    //Ottengo il segno degli estremi e della mediana
    double sign_a{sign(f.Eval(m_a))};
    double sign_b{sign(f.Eval(m_b))};
    double sign_med{sign(f.Eval(med))};
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
        updateRPrec();
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
    updateRPrec();
    found = true;
    return (fabs(m_a-m_b)<m_prec ? med : nan(""));
}

/* Metodi della Secante */
Secante::Secante(){
    found = false;
    m_niterations = 0;
    m_prec = M_PREC;
    m_nmax = N_MAX; 
    r_prec = nan("");
}
Secante::Secante(double prec) {
    found = false;
    m_niterations = 0;
    m_prec = prec;
    m_nmax = N_MAX;
    r_prec = nan("");
}
Secante::~Secante(){}
double Secante::CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec /* = 1e-3 */, unsigned int nmax /* = 100 */){
    if(found==true||m_niterations>=m_nmax){
        //Resettiamo il solutore
        m_niterations = 0;
        found = false;
    }
    updateRPrec();
    /* Passaggio 0 */
    //Impostiamo i parametri di ricerca (controllando che non siano già stati cambiati con setPrecision e setNMax)
    m_prec = (m_prec == M_PREC ? prec : m_prec);
    m_nmax = (m_nmax == N_MAX ? nmax : m_nmax);
    //Impostiamo gli estremi di ricerca
    m_a = xmin;
    m_b = xmax;
    //Calcolo la secante tra f(m_a) e f(m_b)
    double sec0 = m_a - (f.Eval(m_a)*(m_b-m_a))/(f.Eval(m_b)-f.Eval(m_a));
    //Ottengo il segno degli estremi e della mediana
    double sign_a{sign(f.Eval(m_a))};
    double sign_b{sign(f.Eval(m_b))};
    double sign_sec0{sign(f.Eval(sec0))};
    //Controlliamo che gli estremi o la mediana non siano già lo zero della funzione
    if(sign_a==0||sign_b==0){
        found = true;
        return (sign_a == 0 ? m_a : m_b);
    }
    else if(sign_sec0==0){
        m_niterations++;
        if(m_niterations>=m_nmax){
            found = false;
            return nan("");
        }
        found = true;
        return sec0;
    }
    else if(sign_a*sign_b>0){
        found = false;
        return nan("");
    }
    if(fabs(m_a-m_b)<=m_prec){
        found = true;
        return sec0;
    }
    /* Passaggio sium */
    //cerr << m_niterations << " " << fabs(m_a-m_b) << " " << m_a << " " << sign_a << " " << m_b << " " << sign_b << " " << sec0 << " " << sign_sec0 << endl;
    while(fabs(m_a-m_b)>=m_prec){
        updateRPrec();
        if(sign_a*sign_sec0<0){ //Se sta a sx richiamiamo CercaZeri sull'intorno [m_a,med]
            m_niterations++;
            if(m_niterations>=m_nmax){//Controllo se non ha finito i tentativi
                found = false;
                return sec0;
            }
            else if(fabs(m_b-sec0)<=m_prec){//magic
                r_prec = fabs(m_a-sec0);
                found = true;
                return sec0;
            }
            return Secante::CercaZeriReference(m_a, sec0, f, prec, nmax);
        }
        else if(sign_sec0*sign_b<0){ //Se sta a dx richiamiamo CercaZeri sull'intorno [med,m_b]
            m_niterations++;
            if(m_niterations>=m_nmax){ //Controllo se non ha finito i tentativi
                found = false;
                return sec0;
            }
            else if(fabs(m_a-sec0)<=m_prec){//magic
                r_prec = fabs(m_a-sec0);
                found = true;
                return sec0;
            }
            return Secante::CercaZeriReference(sec0, m_b, f, prec, nmax);
        }
    }
    updateRPrec();
    found = true;
    return (fabs(m_a-m_b)<m_prec ? sec0 : nan(""));
}


double sign(double x){
    return x != 0 ? copysign(1.0, x) : 0.0; 
}
