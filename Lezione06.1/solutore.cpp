#include "solutore.hpp"

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
double Solutore::sign(double fx){
    return fx != 0 ? copysign(1.0, fx) : 0.0; 
}
/* Metodo della bisezione */
//Costruttori & co.
Bisezione::Bisezione(){
    found = false;
    m_niterations = 0;
    m_prec = M_PREC;
    m_nmax = N_MAX;
    r_prec = nan("");
}
Bisezione::Bisezione(double prec){
    found = false;
    m_niterations = 0;
    m_prec = prec;
    m_nmax = N_MAX;
    r_prec = nan("");
}
Bisezione::~Bisezione() {}
//Funzione pubblica
double Bisezione::CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec, unsigned int nmax){
    //Resettiamo il solutore
    if(found==true||m_niterations>=m_nmax){
        //cerr << "reset bis " << m_prec;
        found = false;
        m_niterations = 0;
    }
    //Controllare se valgono le ipotesi
    if(sign(f.Eval(xmin))==sign(f.Eval(xmax))){
        found = false;
        return nan("");
    }
    m_a = xmin;
    m_b = xmax;
    m_prec = prec /* (m_prec == M_PREC ? prec : m_prec) */;
    m_nmax = nmax /* (m_nmax == N_MAX ? nmax : m_nmax) */;
    return Bisezione::CercaZeri(f);    
}
//Funzione privata
double Bisezione::CercaZeri(const FunzioneBase & f){
    updateRPrec();
    m_niterations++;
    if(m_niterations>=m_nmax){
        found = false;
        return m_actual;
    }
    else if(r_prec<=m_prec){
        found = true;
        return m_actual;
    }
    m_actual = m_a+(m_b-m_a)/2;
    double sign_a{sign(f.Eval(m_a))};
    double sign_b{sign(f.Eval(m_b))};
    double sign_med{sign(f.Eval(m_actual))};
    //Controlliamo che gli estremi o la mediana non siano già lo zero della funzione
    if(sign_a==0||sign_b==0){
        found = true;
        return (sign_a == 0 ? m_a : m_b);
    }
    else if(sign_med==0){
        found = true;
        return m_actual;
    }
    m_a = (sign_b*sign_med<0?m_actual:m_a);
    m_b = (sign_a*sign_med<0?m_actual:m_b);
    return CercaZeri(f);    
}

/* Metodi della secante */
Secante::Secante() : m_o{0} {
    found = false;
    m_niterations = 0;
    m_prec = M_PREC;
    m_nmax = N_MAX;
    r_prec = nan("");
}
Secante::Secante(double prec) : m_o{0} {
    found = false;
    m_niterations = 0;
    m_prec = prec;
    m_nmax = N_MAX;
    r_prec = nan("");
}
Secante::~Secante() {}
//Funzione pubblica
double Secante::CercaZeriReference(double xmin, double xmax, const FunzioneBase & f, double prec, unsigned int nmax){
    //Resettiamo il solutore
    if(found==true||m_niterations>=m_nmax){
        //cerr << "reset sec" << endl;
        found = false;
        m_niterations = 0;
        r_prec = nan("");
    }
    //Controllare se valgono le ipotesi
    if(sign(f.Eval(xmin))==sign(f.Eval(xmax))){
        found = false;
        return nan("");
    }
    m_a = xmin;
    m_b = xmax;
    m_prec = prec /* (m_prec == M_PREC ? prec : m_prec) */;
    m_nmax = nmax /* (m_nmax == N_MAX ? nmax : m_nmax) */;
    return Secante::CercaZeri(f);    
}
//Funzione privata
double Secante::CercaZeri(const FunzioneBase & f){
    if(r_prec<=m_prec){
        found = true;
        return m_actual;
    }
    m_niterations++;
    if(m_niterations>=m_nmax){
        found = false;
        return m_actual;
    }
    m_actual = m_a - (f.Eval(m_a)*(m_b-m_a))/(f.Eval(m_b)-f.Eval(m_a));
    double sign_a{sign(f.Eval(m_a))};
    double sign_b{sign(f.Eval(m_b))};
    double sign_sec{sign(f.Eval(m_actual))};
    //Controlliamo che gli estremi o la sec0 non siano già lo zero della funzione
    if(sign_a==0||sign_b==0){
        found = true;
        return (sign_a == 0 ? m_a : m_b);
    }
    else if(sign_sec==0){
        found = true;
        return m_actual;
    }
    //Assegniamo i nuovi estremi
    m_o = (sign_b*sign_sec<0?m_a:m_b); //necessario per il calcolo della precisione, conserva l'estremo precedente
    m_a = (sign_b*sign_sec<0?m_actual:m_a);
    m_b = (sign_a*sign_sec<0?m_actual:m_b);
    //Aggiorniamo la precisione
    updateRPrec();
    //Richiamiamo la funzione iterativa
    return CercaZeri(f);    
}

void Secante::updateRPrec(){
    r_prec = fabs(m_actual - m_o);
}