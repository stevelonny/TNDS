#include "funzioni.h"

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

    stampa(ord, ndata);

    // 5. Scrive l'array ordinato in un file
    scrivi("output.txt", ord, ndata);

}


