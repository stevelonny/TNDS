#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double media(double data[],int dim);
double var(double data[], int dim);
double devstd(double data[],int dim);
double * leggi(const char* filename, int ndata);
void stampa(const char * filename, double data[], int dim);
double * copia(double data[], int dim);
void ordina(double vett[],int dim);
double mediana(double data[], int dim);
void scrivi(const char * filename, double data[], int dim);

int main(int argc, const char *argv[]) {

    if (argc<3){
        cout << "Uso del programma: " << argv[0] << " ndata filename" << endl;
        return -1;
    }
    
    int ndata = atoi(argv[1]);
    
    const char* filename = argv[2];

	// 1. Legge i dati dal file

    double* data = leggi(filename, ndata);
    stampa(filename, data, ndata);

    // 2. Calcola la media e la varianza
    
    cout << "Media: " << media(data, ndata) << endl;
    cout << "Deviazione standard: " << devstd(data, ndata) << endl;
    cout << "Varianza: " << var(data, ndata) << endl << endl;

    // 3. Calcola la mediana

    cout << "Mediana: " << mediana(data, ndata) << endl << endl;

    // 4. Visualizza i dati ordinati

    double * ord = copia(data, ndata);
    ordina(ord, ndata);

    stampa("array ordinato", ord, ndata);

    // 5. Scrive l'array ordinato in un file
    scrivi("output.txt", ord, ndata);

}

double media(double data[],int dim){
    double media;
    double somma=0;
    
    for(int i=0; i<dim; i++){
        somma+=data[i];
    }
    media = somma/(double)dim;

    return media;
}

double devstd(double data[],int dim){
    double dev;
    double somma=0;
    double mean=media(data, dim);

    for(int i=0; i<dim; i++){
        somma+=pow((data[i]-mean), 2);
    }
    dev = sqrt(somma/(double)dim);

    return dev;
}

double var(double data[], int dim){

    return pow(devstd(data, dim), 2);
}

double * leggi(const char* filename, int ndata){

    ifstream file_in;
    double * data = new double[ndata];
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

void stampa(const char * filename, double data[], int dim){
    cout << "Dati letti da " << filename << ": " << endl;

    for(int i=0; i<dim; i++){
        cout << data[i] << endl;
    }
    cout << endl;
}

double * copia(double data[], int dim){
    double * vcopy = new double[dim];
    for(int k=0; k<dim; k++){
        vcopy[k]=data[k];
    }
    
    return vcopy;
}

void ordina(double vett[], int dim){
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

double mediana(double data[], int dim){
    double * vcopy = copia(data, dim);
    ordina(vcopy, dim);
    
    if(dim%2 == 0){
        return (vcopy[(dim/2)-1]+vcopy[(dim/2)])/2.;
    }
    else{
        return vcopy[dim/2];
    }
}

void scrivi(const char * filename, double data[], int dim){
    ofstream file_out;
    
    file_out.open(filename);
    for(int i=0; i<dim; i++){
        file_out << data[i] << endl;
    }
    file_out.close();
}

