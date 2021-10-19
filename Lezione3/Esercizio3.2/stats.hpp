#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

#include <vector>
#include <algorithm>

using namespace std;

template <typename T> double Mean(const vector<T> & vett){ //teniamo double che è meglio
    T mean;
    T sum = 0;
    
    for(int i=0; i<vett.size(); i++){
        sum+=vett[i];
    }
    mean = sum/(double)vett.size();

    return mean;
}

template <typename T> double StdDev(const vector<T> &data){
    double dev;
    double sum=0;
    double mean=Mean(data);

    for(int i=0; i<data.size(); i++){
        sum+=pow((data[i]-mean), 2);
    }
    dev = sqrt(sum/(double)data.size());

    return dev;
}

template <typename T> double Variance(const vector<T> &data){
    return pow(StdDev(data), 2);
}

template <typename T> vector<T> Read(const char* filename, int ndata){

    ifstream file_in;
    vector<T> data;
    cerr << "(1/4) Vettore creato con dim " << data.size() << endl;
    file_in.open(filename);
    cerr << "(2/4) Apertura file " << filename << endl;
    if(file_in.fail()){
        cout << "Impossibile aprire il file" << endl;
        exit(-1);
    }
    T temp;
    cerr << "(3/4) Lettura da file" << endl;
    for(int i=0; i<ndata; i++){
        file_in >> temp;
        data.push_back(temp);
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

template <typename T> void Print(const vector<T> &data, int dim){
    for(int i=0; i<dim; i++){
        cout << data[i] << endl;
    }
    cout << endl;
}


template <typename T> double Median(vector<T> &data){
    
    sort(data.begin(), data.end());

    if(data.size()%2 == 0){
        return double((data[(data.size()/2)-1]+data[(data.size()/2)])/2.);
    }
    else{
        return double(data[data.size()/2]);
    }
}

template <typename T> void Write(const char * filename, vector<T> &data, int dim){
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
