#include <iostream>
#include "vettore.h"


using namespace std;

int main(){
    Vettore vnull;
    cout << "Dimensione vettore vnull: " << vnull.GetN() << endl;

    Vettore v(10);
    cout << "Vettore v ha dimensione: " << v.GetN() << endl;

    for(int i=0; i<v.GetN(); i++){
        v.SetComponent(i,double(i*2));
    }

    cout << "Vettore dopo le modifiche: dimensione:" << v.GetN() << endl;
    for(int i=0; i<v.GetN(); i++){
        cout << "i=" << i << ":" << v.GetComponent(i) << endl;
    }

    Vettore w=v;

    cout << "Nuovo vettore w copiato da v ha dimensione:" << w.GetN() << endl;
    for(int i=0; i<w.GetN(); i++){
        cout << "i=" << i << ":" << w.GetComponent(i) << endl;
    }

    cout << "Cambiamo un singolo valore del vettore v, indice 4, val 99" << endl;

    v.SetComponent(4,99);
    cout << "Vettore v: dimensione:" << v.GetN() << endl;
    for(int i=0; i<v.GetN(); i++){
        cout << "i=" << i << ":" << v.GetComponent(i) << endl;
    }
    cout << "Vettore w: dimensione:" << v.GetN() << endl;
    for(int i=0; i<w.GetN(); i++){
        cout << "i=" << i << ":" << w.GetComponent(i) << endl;
    }

    

    return 0;
}