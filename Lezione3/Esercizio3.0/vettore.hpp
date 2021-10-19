#ifndef __Vettore__
#define __Vettore__
#include <iostream>
#include <cassert>

template <typename T> class Vettore {
    public:
        
        Vettore(){
            m_N = 0;
            m_V = NULL;
        };
        
        Vettore(unsigned int dim){
            m_N = (int)dim;
            m_V = new T[m_N];
            for(int i=0; i<m_N; i++){
                m_V[i]= NULL; //così va bene per ogni typename
            }
        }
        ~Vettore(){
            std::cerr << "Calling destructor for Vettore with m_V ref&: " << &m_V << std::endl;
            delete[] m_V;
        }

        unsigned int GetN() const{
            return m_N;
        }

        void SetComponent(unsigned int k, T val){
            assert((k<m_N) && "Indice troppo grande"); 
            m_V[k] = val;
        }

        T GetComponent(unsigned int k) const{
            assert((k<m_N) && "Indice troppo grande"); 
            return m_V[k];
        }

        void Scambia(unsigned int k, unsigned int j){
            assert((k<m_N) && "Indice troppo grande"); 
            assert((j<m_N) && "Indice troppo grande"); 
            T t = GetComponent(k);
            SetComponent(k,GetComponent(j));
            SetComponent(j, t);
        }


        T & operator[](unsigned int index){
            assert((index<m_N) && "Indice troppo grande"); 
            return m_V[index];   
        }

        Vettore(const Vettore &vett){
            m_N = vett.m_N;
            m_V = new T[m_N];
            for (int i=0; i<m_N; i++){
                m_V[i] = vett.m_V[i];
            }
        }

        Vettore & operator=(Vettore&& vett){
            std::cerr << "Calling =operator" << std::endl;
            m_V = nullptr;
            m_N = 0;
            if(m_V != vett.m_V){
                delete[] m_V;
                m_V = vett.m_V;
                m_N = vett.m_N;
        
                vett.m_V = nullptr;
                vett.m_N = 0;

            }
            return *this;
        }

        Vettore(Vettore &&vett){
                m_V = nullptr;
                m_N = 0;

                m_V = vett.m_V;
                m_N = vett.m_N;

                vett.m_V = nullptr;
                vett.m_N = 0;
        }

    private:
        unsigned int m_N;
        T* m_V;
};




#endif