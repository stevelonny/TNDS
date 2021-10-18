#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main(int argc, const char *argv[]) {

    if (argc<3){
        cout << "Uso del programma: " << argv[0] << " ndata filename" << endl;
        return -1;
    }
    
    int ndata = atoi(argv[1]);
    double* data = new double[ndata];
    const char* filename = argv[2];

    ifstream file_in;
    ofstream file_out;

	// 1. Legge i dati dal file

    file_in.open(filename);

    if(file_in.fail()){
        cout << "Impossibile aprire il file" << endl;
        return -2;
    }

    for(int i=0; i<ndata; i++){
        file_in >> data[i];
        // aggiungere controllo fine file
    }

    cout << "Primi 5 dati letti: " << endl;

    for(int i=0; i<5; i++){
        cout << data[i] << endl;
    }
    cout << endl;

    // 2. Calcola la media e la varianza

    double media;
    double somma=0;
    
    for(int i=0; i<ndata; i++){
        somma+=data[i];
    }
    media = somma/(double)ndata;

    double dev;
    somma = 0;

    for(int i=0; i<ndata; i++){
        somma+=pow((data[i]-media), 2);
    }
    dev = sqrt(somma/(double)ndata);

    double var = pow(dev, 2);
    
    cout << "Media: " << media << endl;
    cout << "Deviazione standard: " << dev << endl;
    cout << "Varianza: " << var << endl;

    // 3. Calcola la mediana: copia il vettore di partenza…

    double * vcopy = new double[ndata];
    for(int k=0; k<ndata; k++){
        vcopy[k]=data[k];
    }


    // …poi riordina gli elementi…

    int imin=0;
    double min=0;
    for(int j=0; j<ndata-1; j++){
        imin = j;
        min = vcopy[imin];
        for(int i=j+1; i<ndata; i++){
            if(vcopy[i]<min){
                min = vcopy[i];
                imin = i;
            }
        }
        double c = vcopy[j];
        vcopy[j] = vcopy[imin];
        vcopy[imin] = c;
    }

    // …e infine calcola la mediana

    double mediana = 0;

    if(ndata%2 ==0){
        mediana = (vcopy[(ndata/2)-1]+vcopy[(ndata/2)])/2.;
    }
    else{
        mediana = vcopy[ndata/2];
    }

    cout << "Mediana: " << mediana << endl << endl;

    // 4. Visualizza i dati ordinati

    for(int i=0; i<ndata; i++){
        cout << vcopy[i] << endl;
    }
    cout << endl;

    // 5. Scrive l'array ordinato in un file

    file_out.open("output.txt");
    for(int i=0; i<ndata; i++){
        file_out << vcopy[i] << endl;
    }
    file_out.close();

}

