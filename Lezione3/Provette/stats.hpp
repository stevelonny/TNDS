#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

#include <vector>
#include <algorithm>

using namespace std;

/* Funzioni di statistica base */
//Media
template <typename T> double Mean(const vector<T> & vett){ //teniamo double che è meglio
    T mean;
    T sum = 0;
    
    for(int i=0; i<vett.size(); i++){
        sum+=vett[i];
    }
    mean = sum/(double)vett.size();

    return mean;
}
//Deviazione standard
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
//Deviazionie Standard della media
template <typename T> double MeanStdDev(const vector<T> &data){
    return (StdDev<T>(data)/((double)data.size()));
}
//Varianza
template <typename T> double Variance(const vector<T> &data){
    return pow(StdDev(data), 2);
}
//Mediana
template <typename T> double Median(vector<T> &data){

    sort(data.begin(), data.end());

    if(data.size()%2 == 0){
        return double((data[(data.size()/2)-1]+data[(data.size()/2)])/2.);
    }
    else{
        return double(data[data.size()/2]);
    }
}
/* Lettura da file con numero di valori o tutto */
//Numero di valori
template <typename T> vector<T> Read(const char* filename, unsigned int ndata){
    assert(ndata!=0 && "Numero valori da leggere =0");
    ifstream file_in;
    vector<T> data;
    cerr << "(1/4) Vettore creato" << endl;
    file_in.open(filename);
    cerr << "(2/4) Apertura file: " << filename << endl;
    if(file_in.fail()){
        cerr << "Impossibile aprire il file" << endl;
        exit(-1);
    }
    T temp;
    cerr << "(3/4) Lettura da file" << endl;
    for(int i=0; i<ndata; i++){
        file_in >> temp;
        data.push_back(temp);
        // aggiungere controllo fine file
    }
    cerr << "(4/4) Finito lettura di " << ndata << " valori" << endl;
    return data;
}
//Tutto
template <typename T> vector<T> Read(const char* filename){
    ifstream file_in;
    vector<T> data;
    cerr << "(1/4) Vettore creato" << endl;
    cerr << "(2/4) Apertura file: " << filename << endl;
    file_in.open(filename);
    if(file_in.fail()){
        cerr << "Impossibile aprire il file" << endl;
        exit(-1);
    }
    T temp;
    int c=0;
    cerr << "(3/4) Lettura da file" << endl;
    while(file_in>>temp){ //file>>temp returns false if eof() - better version of spoletini cycle
        data.push_back(temp);
        c++;
    }
    cerr << "(4/4) Finito lettura di " << c << " valori" << endl;
    return data;
}
/* Scrittura a schermo e a file dei vettori */
//Schermo, tutto il vettore
template <typename T> void Print(const vector<T> &data){
    assert(data.size()!=0 && "Vettore vuoto");
    for(int i=0; i<data.size(); i++){
        cout << data[i] << endl;
    }
    cout << endl;
}
//Schermo, con numero di valori e verso
template <typename T> void Print(const vector<T> &data, int nlines){
    assert(nlines!=0 && "Numero di valori passato da leggere =0");
    assert(abs(nlines)<data.size() && "Numero di valori passato da leggere > size vettore");
    assert(data.size()!=0 && "Vettore vuoto");
    if(nlines>0){
        for(int i=0; i<nlines; i++){
            cout << data[i] << endl;
        }
        cout << endl;
    }
    else if(nlines<0){
        for(int i=data.size()-1; i>(data.size()+nlines-1); i--){
            cout << data[i] << endl;
        }
        cout << endl;
    }
}
//Schermo, tutto il vettore con verso
template <typename T> void Print(const vector<T> &data, bool verse){
    assert(data.size()!=0 && "Vettore vuoto");
    if(verse){
        for(int i=0; i<data.size(); i++){
            cout << data[i] << endl;
        }
        cout << endl;
    }
    else{
        for(int i=data.size()-1; i>-1; i--){
            cout << data[i] << endl;
        }
        cout << endl;
    }
}

//File, tutto il vettore
template <typename T> void Print(const vector<T> &data, const char* filename){
    assert(data.size()!=0 && "Vettore vuoto");
    cerr << "(1/4) Apertura file: " << filename << endl;
    ofstream file_out;
    cerr << "(2/4) Scrittura su file di tutto il vettore (" << data.size() << " valori)" << endl;
    file_out.open(filename);
    for(int i=0; i<data.size(); i++){
        file_out << data[i] << endl;
    }
    cerr << "(3/4) Chiusura file" << endl;
    file_out.close();
    cerr << "(4/4) Finito scrittura" << endl;
}
//File, tutto il vettore con verso
template <typename T> void Print(const vector<T> &data, const char* filename, bool verse){
    assert(data.size()!=0 && "Vettore vuoto");
    cerr << "(1/4) Apertura file: " << filename << endl;
    ofstream file_out;
    cerr << "(2/4) Scrittura su file dell'intero vettore (" << data.size() << " valori)";
    file_out.open(filename);
    if(verse){
        cerr << " dall'inizio del vettore" << endl;
        for(int i=0; i<data.size(); i++){
            file_out << data[i] << endl;
        }
    }
    else{
        cerr << " dal fondo del vettore" << endl;
        for(int i=data.size()-1; i>-1; i--){
            file_out << data[i] << endl;
        }
    }
    cerr << "(3/4) Chiusura file" << endl;
    file_out.close();
    cerr << "(4/4) Finito scrittura" << endl;
}
//File, con numero di valori e verso
template <typename T> void Print(const vector<T> &data, const char* filename, int nlines){
    assert(nlines!=0 && "Numero di valori passato da leggere =0");
    assert(abs(nlines)<data.size() && "Numero di valori passato da leggere > size vettore");
    assert(data.size()!=0 && "Vettore vuoto");
    cerr << "(1/4) Apertura file: " << filename << endl;
    ofstream file_out;
    cerr << "(2/4) Scrittura su file di " << abs(nlines) << " valori";
    file_out.open(filename);
    if(nlines>0){
        cerr << " dall'inizio del vettore" << endl;
        for(int i=0; i<nlines; i++){
            file_out << data[i] << endl;
        }
    }
    else if(nlines<0){
        cerr << " dal fondo del vettore" << endl;
        for(int i=data.size()-1; i>(data.size()+nlines-1); i--){
            file_out << data[i] << endl;
        }
    }
    cerr << "(3/4) Chiusura file" << endl;
    file_out.close();
    cerr << "(4/4) Finito scrittura" << endl;
}

