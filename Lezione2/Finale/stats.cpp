#include "stats.h"
#include "vettore.h"

double Mean(const Vettore vett){
    double mean;
    double sum=0;
    
    for(int i=0; i<vett.GetN(); i++){
        sum+=vett.GetComponent(i);
    }
    mean = sum/(double)vett.GetN();

    return mean;
}

double StdDev(const Vettore data){
    double dev;
    double sum=0;
    double mean=Mean(data);

    for(int i=0; i<data.GetN(); i++){
        sum+=pow((data.GetComponent(i)-mean), 2);
    }
    dev = sqrt(sum/(double)data.GetN());

    return dev;
}

double Variance(const Vettore data){
    return pow(StdDev(data), 2);
}

Vettore Read(const char* filename, int ndata){

    ifstream file_in;
    Vettore data(ndata);
    cout << "vettore creato con dim " << data.GetN() << endl;
    file_in.open(filename);

    if(file_in.fail()){
        cout << "Impossibile aprire il file" << endl;
        return -1;
    }
    double t=0;
    for(int i=0; i<ndata; i++){
        file_in >> data[i];
        // aggiungere controllo fine file
    }
    cout << data[0] << " " << data[1] << endl;

    return data;
}

/* void Stampa(const char * filename, double data[], int dim){
    cout << "Dati letti da " << filename << ": " << endl;

    for(int i=0; i<dim; i++){
        cout << data[i] << endl;
    }
    cout << endl;
} */

void Print(const Vettore data, int dim){
    for(int i=0; i<dim; i++){
        cout << data.GetComponent(i) << endl;
    }
    cout << endl;
}

double * CopyFromVettore(const Vettore vett){
    double * vcopy = new double[vett.GetN()];
    for(int k=0; k<vett.GetN(); k++){
        vcopy[k] = vett.GetComponent(k);
    }
    
    return vcopy;
}

void Sort(double * vett, int ndata){
    int dim=ndata;
    int imin=0;
    double min=0;
    for(int j=0; j<dim-1; j++){
        imin = j;
        min = vett[imin];
        for(int i=j+1; i<dim; i++){
            if(vett[i]<min){
                min = vett[i];
                imin = i;
            }
        }
        double c = vett[j];
        vett[j] = vett[imin];
        vett[imin] = c;
    }
}

void Sort(Vettore vett){
    int dim=vett.GetN();
    int imin=0;
    double min=0;
    for(int j=0; j<dim-1; j++){
        imin = j;
        min = vett[imin];
        for(int i=j+1; i<dim; i++){
            if(vett[i]<min){
                min = vett[i];
                imin = i;
            }
        }
        double c = vett[j];
        vett[j] = vett[imin];
        vett[imin] = c;
    }
}

double Median(const Vettore data){
    double * vcopy = CopyFromVettore(data);
    Sort(vcopy, data.GetN());
    
    if(data.GetN()%2 == 0){
        return (vcopy[(data.GetN()/2)-1]+vcopy[(data.GetN()/2)])/2.;
    }
    else{
        return vcopy[data.GetN()/2];
    }
}

void Write(const char * filename, Vettore data, int dim){
    ofstream file_out;
    
    file_out.open(filename);
    for(int i=0; i<dim; i++){
        file_out << data[i] << endl;
    }
    file_out.close();
}
