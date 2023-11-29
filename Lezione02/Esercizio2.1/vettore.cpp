#include <iostream>
#include "vettore.h"
#include <assert.h>

Vettore::Vettore(){
    m_N = 0;
    m_V = NULL;
}

Vettore::Vettore(unsigned int dim){
    m_N = dim;
    m_V = new double[m_N];
    for(int i=0; i<m_N; i++){
        m_V[i] = 0;
    }
}

Vettore::~Vettore(){
    std::cout << "Calling destructor for Vettore with m_V ref&: " << &m_V << std::endl;
    delete[] m_V;
}

unsigned int Vettore::GetN() const{
    return m_N;
}

void Vettore::SetComponent(unsigned int k, double val){
    assert((k<m_N) && "Indice troppo grande"); 
    m_V[k] = val;
}

double Vettore::GetComponent(unsigned int k) const{
    assert((k<m_N) && "Indice troppo grande"); 
    return m_V[k];
    std::cout << "sium" << std::endl;
}

void Vettore::Scambia(unsigned int k, unsigned int j){
    assert((k<m_N) && "Indice troppo grande"); 
    assert((j<m_N) && "Indice troppo grande"); 
    double t = GetComponent(k);
    SetComponent(k,GetComponent(j));
    SetComponent(j, t);
}


double & Vettore::operator[](unsigned int index){
    assert((index<m_N) && "Indice troppo grande"); 
    return m_V[index];   
}

Vettore::Vettore(const Vettore &vett){
    m_N = vett.m_N;
    m_V = new double(m_N);
    for (int i=0; i<m_N; i++){
        m_V[i] = vett.m_V[i];
    }
}

Vettore & Vettore::operator=(Vettore&& vett){
    std::cout << "Calling =operator" << std::endl;
    m_V = nullptr;
    m_N = 0;
    if(m_V != vett.m_V){
        delete[] m_V;
        m_V = vett.m_V;
        m_N = vett.m_N;
        
        /* for(int i=0; i<m_N; i++){
            std::cout << m_V[i] << std::endl;
            m_V[i] = vett.GetComponent(i);
            } */
        vett.m_V = nullptr;
        vett.m_N = 0;

        }
    return *this;
}

Vettore::Vettore(Vettore &&vett){
        m_V = nullptr;
        m_N = 0;

        m_V = vett.m_V;
        m_N = vett.m_N;

        vett.m_V = nullptr;
        vett.m_N = 0;
}
