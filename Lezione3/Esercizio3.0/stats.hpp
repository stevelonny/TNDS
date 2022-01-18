#include "vettore.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

template <typename T> double Mean(const Vettore<T> & vett){ //teniamo double che è meglio
    T mean;
    T sum = 0;
    
    for(int i=0; i<vett.GetN(); i++){
        sum+=vett.GetComponent(i);
    }
    mean = sum/(double)vett.GetN();

    return mean;
}

template <typename T> double StdDev(const Vettore<T> &data){
    double dev;
    double sum=0;
    double mean=Mean(data);

    for(int i=0; i<data.GetN(); i++){
        sum+=pow((data.GetComponent(i)-mean), 2);
    }
    dev = sqrt(sum/(double)data.GetN());

    return dev;
}

template <typename T> double Variance(const Vettore<T> &data){
    return pow(StdDev(data), 2);
}

template <typename T> Vettore<T> Read(const char* filename, int ndata){

    ifstream file_in;
    Vettore<T> data(ndata);
    cerr << "(1/4) Vettore creato con dim " << data.GetN() << endl;
    file_in.open(filename);
    cerr << "(2/4) Apertura file " << filename << endl;
    if(file_in.fail()){
        cout << "Impossibile aprire il file" << endl;
        return -1;
    }
    //double t=0;
    cerr << "(3/4) Lettura da file" << endl;
    for(int i=0; i<ndata; i++){
        file_in >> data[i];
        // aggiungere controllo fine file
    }
    cerr << "(4/4) Finito lettura" << endl;
    return data;
}

/* void Stampa(const char * filename, double data[], int dim){
    cout << "Dati letti da " << filename << ": " << endl;

    for(int i=0; i<dim; i++){
        cout << data[i] << endl;
    }
    cout << endl;
} */

template <typename T> void Print(const Vettore<T> &data, int dim){
    for(int i=0; i<dim; i++){
        cout << data.GetComponent(i) << endl;
    }
    cout << endl;
}

template <typename T> T* CopyFromVettore(const Vettore<T> &vett){
    T * vcopy{new double[vett.GetN()]};
    for(int k=0; k<vett.GetN(); k++){
        vcopy[k] = vett.GetComponent(k);
    }
    
    return vcopy;
}

template <typename T> void Sort(T * vett, int ndata){
    int dim=ndata;
    int imin=0;
    T min=0;
    for(int j=0; j<dim-1; j++){
        imin = j;
        min = vett[imin];
        for(int i=j+1; i<dim; i++){
            if(vett[i]<min){
                min = vett[i];
                imin = i;
            }
        }
        T c{vett[j]};
        vett[j] = vett[imin];
        vett[imin] = c;
    }
}

template <typename T> void Sort(Vettore<T> &vett){
    int dim=vett.GetN();
    int imin=0;
    T min=0;
    for(int j=0; j<dim-1; j++){
        imin = j;
        min = vett[imin];
        for(int i=j+1; i<dim; i++){
            if(vett[i]<min){
                min = vett[i];
                imin = i;
            }
        }
        T c = vett[j];
        vett[j] = vett[imin];
        vett[imin] = c;
    }
}

template <typename T> double Median(const Vettore<T> &data){
    T * vcopy = CopyFromVettore(data);
    Sort(vcopy, data.GetN());
    
    if(data.GetN()%2 == 0){
        return double((vcopy[(data.GetN()/2)-1]+vcopy[(data.GetN()/2)])/2.);
    }
    else{
        return double(vcopy[data.GetN()/2]);
    }
}

template <typename T> void Print(Vettore<T> &data, int dim, const char * filename){
    cerr << "(1/4) Apertura file " << filename << endl;
    ofstream file_out;
    cerr << "(2/4) Scrittura su file" << endl;
    file_out.open(filename);
    for(int i=0; i<dim; i++){
        file_out << data[i] << endl;
    }
    cerr << "(3/4) Chiusura file" << endl;
    file_out.close();
    cerr << "(4/4) Finito scrittura" << endl;
}
