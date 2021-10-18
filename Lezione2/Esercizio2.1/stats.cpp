#include "stats.h"

double Mean(const Vettore vett){
    double media;
    double somma=0;
    
    for(int i=0; i<vett.GetN(); i++){
        somma+=vett.GetComponent(i);
    }
    media = somma/(double)vett.GetN();

    return media;
}

double DevStd(Vettore data){
    double dev;
    double somma=0;
    double mean=Media(data);

    for(int i=0; i<data.GetN(); i++){
        somma+=pow((data.GetComponent(i)-mean), 2);
    }
    dev = sqrt(somma/(double)data.GetN());

    return dev;
}

double Var(Vettore data){
    return pow(DevStd(data), 2);
}

double * Leggi(const char* filename, int ndata){

    ifstream file_in;
    Vettore data(ndata);
    file_in.open(filename);

    if(file_in.fail()){
        cout << "Impossibile aprire il file" << endl;
    }

    for(int i=0; i<ndata; i++){
        file_in >> data[i];
        // aggiungere controllo fine file
    }

    return data;
}

/* void Stampa(const char * filename, double data[], int dim){
    cout << "Dati letti da " << filename << ": " << endl;

    for(int i=0; i<dim; i++){
        cout << data[i] << endl;
    }
    cout << endl;
} */

void Stampa(Vettore data, int dim){
    for(int i=0; i<dim; i++){
        cout << data[i] << endl;
    }
    cout << endl;
}

double * CopiaDaClasse(const Vettore vett){
    double * vcopy = new double[vett.GetN()];
    for(int k=0; k<vett.GetN(); k++){
        vcopy[k] = vett[k];
    }
    
    return vcopy;
}

void Ordina(Vettore vett){
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

double Mediana(const Vettore data){
    double * vcopy = CopiaDaClasse(data);
    Ordina(vcopy, data.GetN());
    
    if(dim%2 == 0){
        return (vcopy[(dim/2)-1]+vcopy[(dim/2)])/2.;
    }
    else{
        return vcopy[dim/2];
    }
}

void Scrivi(const char * filename, double data[], int dim){
    ofstream file_out;
    
    file_out.open(filename);
    for(int i=0; i<dim; i++){
        file_out << data[i] << endl;
    }
    file_out.close();
}
